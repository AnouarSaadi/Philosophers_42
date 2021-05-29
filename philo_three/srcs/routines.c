/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaadi <asaadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/22 14:16:56 by asaadi            #+#    #+#             */
/*   Updated: 2021/05/29 15:25:35 by asaadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

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
		if (sem_wait(ph->protect_die_eat_ph_sem) != 0)
			return (NULL);
		if (get_current_time() > ph->limit)
		{
			ph->is_alive = 0;
			if (sem_wait(data->output_sem) != 0)
				return (NULL);
			printf("%u\t%d\tdied\n", get_current_time() - data->start,
				ph->index + 1);
			sem_post(data->main_sem);
		}
		sem_post(ph->protect_die_eat_ph_sem);
		usleep(500);
	}
	return (arg);
}

void	output_print(t_data *data, t_philo *ph, char *str_to_print, int ms)
{
	if (sem_wait(data->output_sem) != 0)
		return ;
	printf("%u\t%d\t%s\n", get_current_time() - data->start,
		ph->index + 1, str_to_print);
	sem_post(data->output_sem);
	usleep(ms * 1000);
}

int	peer_routine(t_data *data, t_philo *ph)
{
	if (sem_wait(data->forks) != 0)
		return (0);
	output_print(data, ph, "has taken a fork", 0);
	if (sem_wait(data->forks) != 0)
		return (0);
	output_print(data, ph, "has taken a fork", 0);
	if (sem_wait(ph->protect_die_eat_ph_sem) != 0)
		return (0);
	ph->limit = get_current_time() + data->time_to_die;
	output_print(data, ph, "is eating", data->time_to_eat);
	sem_post(ph->protect_die_eat_ph_sem);
	sem_post(data->forks);
	sem_post(data->forks);
	if (data->number_of_times_each_philosopher_must_eat != -1)
	{
		data->meals_counter--;
		if (!data->meals_counter)
		{
			sem_post(data->meals_sem);
			return (0);
		}
	}
	output_print(data, ph, "is sleeping", data->time_to_sleep);
	output_print(data, ph, "is thinking", 0);
	return (1);
}

void	routine(t_philo *ph)
{
	t_data		*data;
	pthread_t	th;

	data = ph->data;
	ph->limit = get_current_time() + data->time_to_die;
	if (pthread_create(&th, NULL, check_life, (void *)ph) != 0)
		sem_post(data->main_sem);
	if (pthread_detach(th) != 0)
		sem_post(data->main_sem);
	while (ph && ph->is_alive)
	{
		if (!peer_routine(data, ph))
			break ;
	}
}
