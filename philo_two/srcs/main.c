/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaadi <asaadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 13:34:29 by asaadi            #+#    #+#             */
/*   Updated: 2021/05/25 17:07:17 by asaadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

int	main(int ac, char **av)
{
	t_data	*data;

	if (ac < 5 || ac > 6)
		return (ft_put_err_fd("Philo_two: wrong number of arguments",
				2, -1, NULL));
	data = malloc(sizeof(t_data));
	if (!data)
		return (ft_put_err_fd("Philo_two: failed to allocate memory",
				2, -1, NULL));
	if (!parser_args(data, av))
		return (fail_check("Philo_two: invalid arguments", data));
	data->main_sem = semaphore_open("/main", 0);
	if (data->main_sem == SEM_FAILED)
		return (fail_check("Philo_two: Failed to create the main semaphore",
				data));
	if (!ph_struct__init(data))
		sem_post(data->main_sem);
	if (!creat_detach_threads(data))
		sem_post(data->main_sem);
	sem_wait(data->main_sem);
	sem_post(data->main_sem);
	ft_clear_data(data);
	return (0);
}
