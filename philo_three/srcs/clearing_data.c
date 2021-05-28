/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clearing_data.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaadi <asaadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 16:10:02 by asaadi            #+#    #+#             */
/*   Updated: 2021/05/28 16:52:59 by asaadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void	ft_free_pointer(void **ptr)
{
	free(*ptr);
	*ptr = NULL;
}

void	ft_clear_data(t_data *data)
{
	int	index;

	index = -1;
	while (++index < data->number_of_philosophers)
	{
		sem_unlink("/protect_ph");
		kill(data->pid[index], SIGKILL);
	}
	ft_free_pointer((void **)&data->pid);
	sem_unlink("/fork");
	ft_free_pointer((void **)&data->ph);
	sem_unlink("/main");
	sem_unlink("/output");
	if (data->number_of_times_each_philosopher_must_eat != -1)
		sem_unlink("/meals");
	ft_free_pointer((void **)&data);
}
