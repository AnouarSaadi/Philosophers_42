/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaadi <asaadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 18:40:35 by asaadi            #+#    #+#             */
/*   Updated: 2021/05/28 16:35:33 by asaadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_THREE_H
# define PHILO_THREE_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>
# include <semaphore.h>
# include <fcntl.h>
# include <string.h>
# include <errno.h>
# include <signal.h>

typedef struct s_data	t_data;

typedef struct s_philo
{
	unsigned int	limit;
	int				index;
	char			is_alive;
	t_data			*data;
	sem_t			*protect_die_eat_ph_sem;
}	t_philo;

struct	s_data
{
	pthread_t		th;
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_times_each_philosopher_must_eat;
	unsigned int	start;
	sem_t			*forks;
	t_philo			*ph;
	pid_t			*pid;
	sem_t			*main_sem;
	sem_t			*output_sem;
	sem_t			*meals_sem;
	int				meals_counter;
};

int				ft_atoi(const char *str);
int				parser_args(t_data *data, char **av);
void			ft_free_pointer(void **array);
void			ft_clear_data(t_data *data);
int				ft_put_err_fd(char *s, int fd, int ret, t_data *data);
int				fail_check(char *str_to_put, t_data *data);
unsigned int	get_current_time(void);
void			*check_life(void *arg);
void			routine(t_philo *ph);
int				ph_struct__init(t_data *data);
int				creat__processes(t_data *data);
sem_t			*semaphore_open(char *name, int init_value);

#endif
