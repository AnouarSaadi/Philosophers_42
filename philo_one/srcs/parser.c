/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaadi <asaadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 15:29:16 by asaadi            #+#    #+#             */
/*   Updated: 2021/05/25 15:27:18 by asaadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int	check_args(t_data *data)
{
	if (data->time_to_eat <= 0
		|| data->time_to_die <= 0
		|| data->time_to_sleep <= 0)
		return (0);
	return (1);
}

int	parser_args(t_data *data, char **av)
{
	data->number_of_philosophers = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (av[5])
	{
		data->number_of_times_each_philosopher_must_eat = ft_atoi(av[5]);
		if (data->number_of_times_each_philosopher_must_eat <= 0)
			return (0);
	}
	else if (!av[5])
		data->number_of_times_each_philosopher_must_eat = -1;
	if (!check_args(data))
		return (0);
	data->forks = malloc(sizeof(pthread_mutex_t)
			* data->number_of_philosophers);
	data->ph = malloc(sizeof(t_philo) * data->number_of_philosophers);
	return (1);
}
