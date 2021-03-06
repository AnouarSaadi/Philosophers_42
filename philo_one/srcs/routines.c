/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaadi <asaadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/22 14:16:56 by asaadi            #+#    #+#             */
/*   Updated: 2021/05/30 11:49:35 by asaadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

unsigned int	get_current_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	*check_life(void *arg)
{
	t_philo	*ph;
	t_data	*data;

	ph = (t_philo *)arg;
	data = ph->data;
	while (ph && ph->is_alive)
	{
		pthread_mutex_lock(&ph->protect_die_eat_ph_mutex);
		if (get_current_time() > ph->limit)
		{
			ph->is_alive = 0;
			pthread_mutex_lock(&data->output_mutex);
			printf("%u\t%d died\n", get_current_time() - data->start,
				ph->index + 1);
			pthread_mutex_unlock(&data->main_mutex);
		}
		pthread_mutex_unlock(&ph->protect_die_eat_ph_mutex);
		usleep(500);
	}
	return (arg);
}

void	output_print(t_data *data, t_philo *ph, char *str_to_print, int ms_time)
{
	if (pthread_mutex_lock(&data->output_mutex) < 0)
		return ;
	printf("%u\t%d %s\n", get_current_time() - data->start,
		ph->index + 1, str_to_print);
	pthread_mutex_unlock(&data->output_mutex);
	usleep(ms_time * 1000);
}

int	peer_routine(t_data *data, t_philo *ph)
{
	pthread_mutex_lock(&data->forks[ph->l_fork]);
	output_print(data, ph, "has taken a fork", 0);
	pthread_mutex_lock(&data->forks[ph->r_fork]);
	output_print(data, ph, "has taken a fork", 0);
	pthread_mutex_lock(&ph->protect_die_eat_ph_mutex);
	ph->limit = get_current_time() + data->time_to_die;
	output_print(data, ph, "is eating", data->time_to_eat);
	pthread_mutex_unlock(&ph->protect_die_eat_ph_mutex);
	pthread_mutex_unlock(&data->forks[ph->l_fork]);
	pthread_mutex_unlock(&data->forks[ph->r_fork]);
	if (++ph->eating_times == data->number_of_times_each_philosopher_must_eat)
	{
		data->decrement_eat--;
		ph->is_alive = 0;
		return (0);
	}
	output_print(data, ph, "is sleeping", data->time_to_sleep);
	output_print(data, ph, "is thinking", 0);
	return (1);
}

void	*routine(void *arg)
{
	t_philo		*ph;
	t_data		*data;
	pthread_t	th;

	ph = (t_philo *)arg;
	data = ph->data;
	ph->limit = get_current_time() + data->time_to_die;
	if (pthread_create(&th, NULL, check_life, (void *)ph) != 0)
		pthread_mutex_unlock(&data->main_mutex);
	if (pthread_detach(th) != 0)
		pthread_mutex_unlock(&data->main_mutex);
	while (ph && ph->is_alive)
	{
		if (!peer_routine(data, ph))
			break ;
	}
	return (arg);
}
