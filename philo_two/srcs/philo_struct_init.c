/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_struct_init.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaadi <asaadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/22 14:22:52 by asaadi            #+#    #+#             */
/*   Updated: 2021/05/28 19:26:03 by asaadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

void	*eating_checker(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	while (data->decrement_eat)
		usleep(100);
	sem_wait(data->output_sem);
	printf("Philo_two: each philo has eaten %d times\n",
		data->number_of_times_each_philosopher_must_eat);
	sem_post(data->main_sem);
	return (arg);
}

sem_t	*semaphore_open(char *name, int init_value)
{
	sem_t	*ret;

	sem_unlink(name);
	ret = sem_open(name, O_CREAT, S_IWUSR | S_IRUSR, init_value);
	return (ret);
}

int	ph_struct__init(t_data *data)
{
	int	index;

	index = -1;
	while (++index < data->number_of_philosophers)
	{
		data->ph[index].index = index;
		data->ph[index].is_alive = 1;
		data->ph[index].eating_times = 0;
		data->ph[index].data = data;
		data->ph[index].protect_die_eat_ph_sem = semaphore_open("/protect", 1);
	}
	data->forks = semaphore_open("/forks", data->number_of_philosophers);
	if (data->forks == SEM_FAILED)
		return (0);
	if (data->number_of_times_each_philosopher_must_eat != -1)
	{
		data->decrement_eat = data->number_of_philosophers;
		if (pthread_create(&data->th, NULL, eating_checker, (void *)data) != 0)
			return (ft_put_err_fd("Philo_two: Failed to create thread",
					2, 0, data));
		if (pthread_detach(data->th) != 0)
			return (ft_put_err_fd("Philo_two: Failed to create thread",
					2, 0, data));
	}
	return (1);
}
