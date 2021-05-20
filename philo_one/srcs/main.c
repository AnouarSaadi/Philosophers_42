/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaadi <asaadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 13:34:29 by asaadi            #+#    #+#             */
/*   Updated: 2021/05/20 17:42:27 by asaadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

// printf("\033[1;91m              DEBUGGING!!!\033[0m\n");


void    ft_putstr_fd(char *s, int fd)
{
    while (*s)
        write(fd, s++, 1);
    write(1, "\n", 1);
}

// void   *print_msg(void *arg)
// {
//     int philo;

//     philo = *(int *)arg;
//     pthread_mutex_lock(&mutex);
//     printf("Philo %d\n", philo);
//     pthread_mutex_unlock(&mutex);
//     free(arg);
//     return (arg);
// }

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
    while (ph->alive)
    {
        if (get_time() > ph->limit)
        {
            pthread_mutex_lock(&data->output_mutex);
            ph->alive = 0;
            printf("%u\t%d died\n", get_time() - data->start, ph->index + 1);
            pthread_mutex_unlock(&data->main_mutex);
        }
        usleep(100);
    }
    return (arg);
}

void    *routine(void *arg)
{
    t_philo *ph;
    t_data *data;
    pthread_t th;


    ph = (t_philo*)arg;
    data = ph->data;
    ph->limit = get_time() + data->time_to_die;
    pthread_create(&th, NULL, check_life, (void *)ph);
    pthread_detach(th);
    while (ph->alive)
    {
        // taking forks
        // (1)
        pthread_mutex_lock(&data->forks[ph->lf]);

        pthread_mutex_lock(&data->output_mutex);
        printf("%u\t%d has taken a fork\n", get_time() - data->start, ph->index + 1);
        pthread_mutex_unlock(&data->output_mutex);
        
        // (2)
        pthread_mutex_lock(&data->forks[ph->rf]);
 
        pthread_mutex_lock(&data->output_mutex);
        printf("%u\t%d has taken a fork\n", get_time() - data->start, ph->index + 1);
        pthread_mutex_unlock(&data->output_mutex);
 
        // eating
        pthread_mutex_lock(&data->output_mutex);
        printf("%u\t%d is eating\n", get_time() - data->start, ph->index + 1);
        pthread_mutex_unlock(&data->output_mutex);
        ph->limit = get_time() + data->time_to_die;
        usleep(data->time_to_eat * 1000);
        if (++ph->eating_times == data->number_of_times_each_philosopher_must_eat)
        {
            data->decrement_eat--;
            break;
        }
        // drop forks
        pthread_mutex_unlock(&data->forks[ph->lf]);
        pthread_mutex_unlock(&data->forks[ph->rf]);
 
        // sleeping
        pthread_mutex_lock(&data->output_mutex);
        printf("%u\t%d is sleeping\n", get_time() - data->start, ph->index + 1);
        pthread_mutex_unlock(&data->output_mutex);
        usleep(data->time_to_sleep * 1000);
        // thinking
        pthread_mutex_lock(&data->output_mutex);
        printf("%u\t%d is thinking\n", get_time() - data->start, ph->index + 1);
        pthread_mutex_unlock(&data->output_mutex);
    }
    return (arg);
}

void parser_args(t_data *data, char **av)
{
    data->number_of_philosophers = ft_atoi(av[1]);
    data->time_to_die = ft_atoi(av[2]);
    data->time_to_eat = ft_atoi(av[3]);
    data->time_to_sleep = ft_atoi(av[4]);
    if (av[5])
        data->number_of_times_each_philosopher_must_eat = ft_atoi(av[5]);
    else if (!av[5])
        data->number_of_times_each_philosopher_must_eat = -1;
    data->forks = malloc(sizeof(pthread_mutex_t) * data->number_of_philosophers);
    data->ph = malloc(sizeof(t_philo) * data->number_of_philosophers);
}

t_data *init_struct_data(void)
{
    t_data *data;

    data = malloc(sizeof(t_data));
    return (data);
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

int main(int ac, char **av)
{
    t_data  *data;
    int i;


    if (ac < 5 || ac > 6)
    {
        printf("Error in the argments number\n");
        return (-1);
    }
    data = init_struct_data();
    parser_args(data, av);
    pthread_mutex_init(&data->main_mutex, NULL);
    pthread_mutex_init(&data->output_mutex, NULL);
    i = -1;
    while (++i < data->number_of_philosophers)
    {
        data->ph[i].index = i;
        data->ph[i].lf = i;
        data->ph[i].rf = (i + 1) % data->number_of_philosophers;
        data->ph[i].alive = 1;
        data->ph[i].data = data;
        data->ph[i].eating_times = 0;
    }
    if (data->number_of_times_each_philosopher_must_eat != -1)
    {
        pthread_create(&data->th, NULL, eating_checker, (void*)data);
        pthread_detach(data->th);
    }
    pthread_mutex_lock(&data->main_mutex);
    data->start = get_time();
    data->decrement_eat = data->number_of_philosophers;
    i = -1;
    while (++i < data->number_of_philosophers)
    {
        if (pthread_create(&data->th, NULL, routine, (void*)&data->ph[i]) != 0)
        {
            ft_putstr_fd("Failed to create thread", 2);
            return (-1);
        }
        if (pthread_detach(data->th) != 0)
        {
            ft_putstr_fd("Failed to detach thread", 2);
            return (-1);
        }
    }
    pthread_mutex_lock(&data->main_mutex);
    pthread_mutex_unlock(&data->main_mutex);

// clean memory - destroy mutexes

    return (0);
}