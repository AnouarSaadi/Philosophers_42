/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaadi <asaadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 15:29:16 by asaadi            #+#    #+#             */
/*   Updated: 2021/05/29 14:59:47 by asaadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int	is_digit(char **av)
{
	int	i;
	int	j;

	i = 1;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (av[i][0] == '-' && (av[i][1] >= '0' && av[i][1] <= '9'))
				j++;
			if (!(av[i][j] >= '0' && av[i][j] <= '9'))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	check_args(t_data *data)
{
	if (data->number_of_philosophers <= 0
		|| data->time_to_eat <= 0
		|| data->time_to_die <= 0
		|| data->time_to_sleep <= 0)
		return (0);
	return (1);
}

int	parser_args(t_data *data, char **av)
{
	if (!is_digit(av))
		return (0);
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
	data->ph = malloc(sizeof(t_philo) * data->number_of_philosophers + 1);
	data->pid = malloc(sizeof(pid_t) * data->number_of_philosophers + 1);
	return (1);
}
