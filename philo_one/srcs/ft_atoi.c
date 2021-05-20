/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaadi <asaadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 18:36:34 by asaadi            #+#    #+#             */
/*   Updated: 2021/05/19 15:53:30 by asaadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static int	ft_long(long res, int sign)
{
	if (res < 0 && sign > 0)
		return (-1);
	if (res > 0 && sign < 0)
		return (0);
	return (res);
}

int			ft_atoi(const char *str)
{
	long		res;
	int			sign;
	int			i;

	if (!*str)
		return (0);
	res = 0;
	sign = 1;
	i = 0;
	while ((str[i] == '\t' || str[i] == '\n' || str[i] == '\v' ||
				str[i] == '\f' || str[i] == '\r' || str[i] == ' ') && str[i])
		i++;
	if ((str[i] == '-' || str[i] == '+') && str[i])
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while ((str[i] >= '0' && str[i] <= '9') && str[i])
	{
		res = res * 10 + (str[i] - '0');
		i++;
	}
	res = sign * res;
	return (ft_long(res, sign));
}
