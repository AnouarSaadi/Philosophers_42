/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaadi <asaadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 13:34:29 by asaadi            #+#    #+#             */
/*   Updated: 2021/05/22 16:11:07 by asaadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

int	main(int ac, char **av)
{
	t_data	*data;

	if (ac < 5 || ac > 6)
		return (ft_put_err_fd("Philo_two: wrong number of arguments",
				2, 0, NULL));
	data = malloc(sizeof(t_data));
	if (!data)
		return (ft_put_err_fd("Philo_two: failed to allocate memory",
				2, 0, NULL));
	if (!parser_args(data, av))
	{
		ft_free_pointer((void **)&data);
		return (ft_put_err_fd("Philo_two: invalid arguments",
				2, 0, NULL));
	}
	pthread_mutex_init(&data->main_mutex, NULL);
	pthread_mutex_lock(&data->main_mutex);
	if (!ph_struct__init(data))
		return (-1);
	if (!creat_detach_threads(data))
		return (-1);
	pthread_mutex_lock(&data->main_mutex);
	pthread_mutex_unlock(&data->main_mutex);
	ft_clear_data(data);
	return (0);
}
