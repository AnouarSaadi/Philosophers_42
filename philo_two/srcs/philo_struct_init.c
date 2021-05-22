/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_struct_init.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaadi <asaadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/22 14:22:52 by asaadi            #+#    #+#             */
/*   Updated: 2021/05/22 16:12:17 by asaadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

void	*eating_checker(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	while (data->decrement_eat)
		usleep(100);
	pthread_mutex_lock(&data->output_mutex);
	pthread_mutex_unlock(&data->main_mutex);
	return (arg);
}

int	ph_struct__init(t_data *data)
{
	int	index;

	index = -1;
	while (++index < data->number_of_philosophers)
	{
		data->ph[index].index = index;
		data->ph[index].l_fork = index;
		data->ph[index].r_fork = (index + 1) % data->number_of_philosophers;
		data->ph[index].is_alive = 1;
		data->ph[index].data = data;
		data->ph[index].eating_times = 0;
		pthread_mutex_init(&data->ph[index].protect_die_eat_ph_mutex, NULL);
		pthread_mutex_init(&data->forks[index], NULL);
	}
	data->decrement_eat = data->number_of_philosophers;
	if (data->number_of_times_each_philosopher_must_eat != -1)
	{
		if (pthread_create(&data->th, NULL, eating_checker, (void *)data) != 0)
			return (ft_put_err_fd("Philo_two: Failed to create thread",
					2, 0, data));
		if (pthread_detach(data->th) != 0)
			return (ft_put_err_fd("Philo_two: Failed to create thread",
					2, 0, data));
	}
	return (1);
}
