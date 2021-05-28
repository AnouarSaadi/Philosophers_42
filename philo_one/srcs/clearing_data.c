/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clearing_data.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaadi <asaadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 16:10:02 by asaadi            #+#    #+#             */
/*   Updated: 2021/05/27 14:12:37 by asaadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

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
		pthread_mutex_destroy(&data->ph[index].protect_die_eat_ph_mutex);
		pthread_mutex_destroy(&data->forks[index]);
	}
	ft_free_pointer((void **)&data->ph);
	ft_free_pointer((void **)&data->forks);
	pthread_mutex_destroy(&data->main_mutex);
	pthread_mutex_destroy(&data->output_mutex);
	ft_free_pointer((void **)&data);
}
