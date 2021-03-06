/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaadi <asaadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 18:42:34 by asaadi            #+#    #+#             */
/*   Updated: 2021/05/28 16:35:20 by asaadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int	main(int ac, char **av)
{
	t_data	*data;

	if (ac < 5 || ac > 6)
		return (ft_put_err_fd("Philo_three: wrong number of arguments",
				2, -1, NULL));
	data = malloc(sizeof(t_data));
	if (!data)
		return (ft_put_err_fd("Philo_three: failed to allocate memory",
				2, -1, NULL));
	if (!parser_args(data, av))
		return (fail_check("Philo_three: invalid arguments", data));
	data->main_sem = semaphore_open("/main", 0);
	if (data->main_sem == SEM_FAILED)
		return (fail_check("Philo_three: Failed to create the main semaphore",
				data));
	if (!ph_struct__init(data))
		sem_post(data->main_sem);
	if (!creat__processes(data))
		sem_post(data->main_sem);
	sem_wait(data->main_sem);
	sem_post(data->main_sem);
	ft_clear_data(data);
	return (0);
}
