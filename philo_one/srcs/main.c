/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaadi <asaadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 13:34:29 by asaadi            #+#    #+#             */
/*   Updated: 2021/05/21 19:45:40 by asaadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int    ft_putstr_fd(char *s, int fd, int ret)
{
    while (*s)
        write(fd, s++, 1);
    write(fd, "\n", 1);
    return (ret);
}

unsigned int get_time(void)
{
    struct timeval time;

    gettimeofday(&time, NULL);
    return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void *check_life(void *arg)
{
    t_philo *ph;
    t_data *data;
    
    ph = (t_philo*)arg;
    data = ph->data;
    while (ph->is_alive)
    {
        pthread_mutex_lock(&ph->protect_die_eat_ph_mutex);
        if (get_time() > ph->limit)
        {
            ph->is_alive = 0;
            pthread_mutex_lock(&data->output_mutex);
            printf("%u\t%d died\n", get_time() - data->start, ph->index + 1);
            pthread_mutex_unlock(&data->main_mutex);
        }
        pthread_mutex_unlock(&ph->protect_die_eat_ph_mutex);
        usleep(100);
    }
    return (arg);
}

void    output_print(t_data *data, t_philo *ph, char *str_to_print)
{
    pthread_mutex_lock(&data->output_mutex);
    printf("%u\t%d %s\n", get_time() - data->start, ph->index + 1, str_to_print);
    pthread_mutex_unlock(&data->output_mutex);
}

void    *routine(void *arg)
{
    t_philo     *ph;
    t_data      *data;
    pthread_t   th;

    ph = (t_philo*)arg;
    data = ph->data;
    ph->limit = get_time() + data->time_to_die;
    pthread_create(&th, NULL, check_life, (void *)ph);
    pthread_detach(th);
    while (ph->is_alive)
    {
        // taking forks
        // (1)
        pthread_mutex_lock(&data->forks[ph->l_fork]);
        output_print(data, ph, "has taken a fork");

        // (2)
        pthread_mutex_lock(&data->forks[ph->r_fork]);
        output_print(data, ph, "has taken a fork");

        // eating
        pthread_mutex_lock(&ph->protect_die_eat_ph_mutex);
        ph->limit = get_time() + data->time_to_die;
        output_print(data, ph, "is eating");
        usleep(data->time_to_eat * 1000);
        pthread_mutex_unlock(&ph->protect_die_eat_ph_mutex);
        pthread_mutex_unlock(&data->forks[ph->l_fork]);
        pthread_mutex_unlock(&data->forks[ph->r_fork]);
        if (++ph->eating_times == data->number_of_times_each_philosopher_must_eat)
        {
            data->decrement_eat--;
            break;
        }
        // drop forks
        // sleeping
        output_print(data, ph, "is sleeping");
        usleep(data->time_to_sleep * 1000);
        // thinking
        output_print(data, ph, "is thinking");
    }
    return (arg);
}

void *eating_checker(void *arg)
{
    t_data *data;


    data = (t_data *)arg;
    while (data->decrement_eat)
        usleep(100);
    pthread_mutex_lock(&data->output_mutex);
    pthread_mutex_unlock(&data->main_mutex);
    return (arg);
}

// int check_arguments()
// {
    
// }

void ph_struct__init(t_data *data)
{
    int index;

    index = -1;
    while (++index < data->number_of_philosophers)
    {
        data->ph[index].index = index;
        data->ph[index].l_fork = index;
        data->ph[index].r_fork = (index + 1) % data->number_of_philosophers;
        data->ph[index].is_alive = 1;
        data->ph[index].data = data;
        data->ph[index].eating_times = 0;
        pthread_mutex_init(&data->ph[index].protect_die_eat_ph_mutex, NULL);
        pthread_mutex_init(&data->forks[index], NULL);
    }
    data->start = get_time();
    data->decrement_eat = data->number_of_philosophers;
}


int main(int ac, char **av)
{
    t_data  *data;
    int index;


    if (ac < 5 || ac > 6)
            return (ft_putstr_fd("Philosophers: philo_one: Error in the arguments", 2, -1));
    data = malloc(sizeof(t_data));
    if (!data)
        return (ft_putstr_fd("Philosophers: philo_one: Failed to allocate memory", 2, -1));
    if (!parser_args(data, av))
    {
        ft_free_pointer((void**)&data);
        return (ft_putstr_fd("Philosophers: philo_one: Error in the arguments", 2, -1));
    }

    pthread_mutex_init(&data->main_mutex, NULL);
    pthread_mutex_init(&data->output_mutex, NULL);
    ph_struct__init(data);
    if (data->number_of_times_each_philosopher_must_eat != -1)
    {
        if (pthread_create(&data->th, NULL, eating_checker, (void*)data) != 0)
            return (ft_putstr_fd("Philosophers: philo_one: Failed to create thread", 2, -1));
        if (pthread_detach(data->th) != 0)
            return (ft_putstr_fd("Philosophers: philo_one: Failed to create thread", 2, -1));
    }
    pthread_mutex_lock(&data->main_mutex);
    index = -1;
    while (++index < data->number_of_philosophers)
    {
        if (pthread_create(&data->th, NULL, routine, (void*)&data->ph[index]) != 0)
            return (ft_putstr_fd("Philosophers: philo_one: Failed to create thread", 2, -1));
        if (pthread_detach(data->th) != 0)
            return (ft_putstr_fd("Philosophers: philo_one: Failed to detach thread", 2, -1));
        usleep(100);
    }
    pthread_mutex_lock(&data->main_mutex);
    pthread_mutex_unlock(&data->main_mutex);
    ft_clear_data(data);
    return (0);
}
