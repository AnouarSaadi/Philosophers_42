/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaadi <asaadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 13:34:29 by asaadi            #+#    #+#             */
/*   Updated: 2021/05/18 15:00:29 by asaadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

pthread_mutex_t mutex;

void    ft_putstr_fd(char *s, int fd)
{
    while (*s)
        write(fd, s++, 1);
}

void   *print_msg(void *arg)
{
    pthread_mutex_lock(&mutex);
    ft_putstr_fd((char*)arg, 1);
    write(1, "\n", 1);
    pthread_mutex_unlock(&mutex);
    return (arg);
}

int main(int ac, char **av)
{
    (void)ac;
    (void)av;
    pthread_t thread0;
    pthread_t thread1;
    char *msg0 = "thread0";
    char *msg1 = "thread1";
    int ret[2];

    pthread_mutex_init(&mutex, NULL);
    ret[0] = pthread_create(&thread0, NULL, print_msg, (void*)msg0);
    ret[1] = pthread_create(&thread1, NULL, print_msg, (void*)msg1);

    pthread_join(thread0, NULL);
    pthread_join(thread1, NULL);
    pthread_mutex_destroy(&mutex);
    // printf("ret0 == %d \n", ret[0]);
    return (0);
}