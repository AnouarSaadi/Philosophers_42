/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaadi <asaadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 13:37:28 by asaadi            #+#    #+#             */
/*   Updated: 2021/05/23 11:28:06 by asaadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_data	t_data;

typedef struct s_philo
{
	unsigned int	limit;
	int				index;
	int				l_fork;
	int				r_fork;
	char			is_alive;
	int				eating_times;
	t_data			*data;
	pthread_mutex_t	protect_die_eat_ph_mutex;
}	t_philo;

struct	s_data
{
	pthread_t		th;
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_times_each_philosopher_must_eat;
	int				decrement_eat;
	unsigned int	start;
	pthread_mutex_t	*forks;
	t_philo			*ph;
	pthread_mutex_t	main_mutex;
	pthread_mutex_t	output_mutex;
};

int				ft_atoi(const char *str);
int				parser_args(t_data *data, char **av);
void			ft_free_pointer(void **array);
void			ft_clear_data(t_data *data);
int				ft_put_err_fd(char *s, int fd, int ret, t_data *data);
unsigned int	get_time(void);
void			*check_life(void *arg);
void			*routine(void *arg);
int				ph_struct__init(t_data *data);
int				creat_detach_threads(t_data *data);

#endif
