/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_detach_threads.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaadi <asaadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/22 14:24:17 by asaadi            #+#    #+#             */
/*   Updated: 2021/05/23 11:28:01 by asaadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int	ft_put_err_fd(char *s, int fd, int ret, t_data *data)
{
	while (*s)
		write(fd, s++, 1);
	write(fd, "\n", 1);
	if (data)
		ft_clear_data(data);
	return (ret);
}

int	creat_detach_threads(t_data *data)
{
	int	index;

	index = -1;
	data->start = get_time();
	pthread_mutex_init(&data->output_mutex, NULL);
	while (++index < data->number_of_philosophers)
	{
		if (pthread_create(&data->th, NULL, routine,
				(void *)&data->ph[index]) != 0)
			return (ft_put_err_fd("Philo_one: failed to create thread",
					2, 0, data));
		if (pthread_detach(data->th) != 0)
			return (ft_put_err_fd("Philo_one: failed to detach thread",
					2, 0, data));
		usleep(100);
	}
	return (1);
}
