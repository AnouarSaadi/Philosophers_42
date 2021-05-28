/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create__processes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaadi <asaadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/22 14:24:17 by asaadi            #+#    #+#             */
/*   Updated: 2021/05/28 17:12:18 by asaadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int	ft_put_err_fd(char *s, int fd, int ret, t_data *data)
{
	while (*s)
		write(fd, s++, 1);
	write(fd, "\n", 1);
	if (data)
		ft_clear_data(data);
	return (ret);
}

int	fail_check(char *str_to_put, t_data *data)
{
	ft_free_pointer((void **)&data);
	return (ft_put_err_fd(str_to_put, 2, -1, NULL));
}

int	creat__processes(t_data *data)
{
	int	index;

	index = -1;
	data->start = get_current_time();
	data->output_sem = semaphore_open("/output", 1);
	if (data->output_sem == SEM_FAILED)
		return (0);
	while (++index < data->number_of_philosophers)
	{
		data->pid[index] = fork();
		if (data->pid[index] == 0)
		{
			routine(&data->ph[index]);
			exit(0);
		}
		else if (data->pid[index] < 0)
			return (ft_put_err_fd("Philo_three: failed to create a process",
					2, 0, data));
		usleep(100);
	}
	return (1);
}
