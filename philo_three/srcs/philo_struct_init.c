/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_struct_init.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaadi <asaadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/22 14:22:52 by asaadi            #+#    #+#             */
/*   Updated: 2021/05/28 17:26:59 by asaadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void	*check_eating_of_ph(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)arg;
	i = -1;
	while (++i < data->number_of_philosophers)
		sem_wait(data->meals_sem);
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

int	create_eating_thread(t_data *data)
{
	pthread_t	th;

	data->meals_sem = semaphore_open("/meals", 0);
	if (data->meals_sem == SEM_FAILED)
		return (0);
	data->meals_counter = data->number_of_times_each_philosopher_must_eat;
	if (pthread_create(&th, NULL, check_eating_of_ph, (void *)data) != 0)
		return (ft_put_err_fd("Philo_one: Failed to create thread",
				2, 0, data));
	if (pthread_detach(th) != 0)
		return (ft_put_err_fd("Philo_one: Failed to create thread",
				2, 0, data));
	return (1);
}

int	ph_struct__init(t_data *data)
{
	int			index;

	index = -1;
	while (++index < data->number_of_philosophers)
	{
		data->ph[index].index = index;
		data->ph[index].is_alive = 1;
		data->ph[index].data = data;
		data->ph[index].protect_die_eat_ph_sem = semaphore_open("/protect", 1);
	}
	data->forks = semaphore_open("/forks", data->number_of_philosophers);
	if (data->forks == SEM_FAILED)
		return (0);
	if (data->number_of_times_each_philosopher_must_eat != -1)
		return (create_eating_thread(data));
	return (1);
}
