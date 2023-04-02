/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maddou <maddou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 12:16:16 by maddou            #+#    #+#             */
/*   Updated: 2023/04/02 17:23:39 by maddou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <pthread.h>
# include <stdio.h>
#include <unistd.h>
# include <stdlib.h>
#include <sys/time.h>

typedef struct thread_s
{
    int i;
    int j;
    int die;
    int *return_thread;
    int return_join;
    int cont_to_eat;
    int number_of_philo;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int number_of_times_each_philosopher_must_eat;
    long long start;
    long long start_programe;
    long long timestamp;
    pthread_t th;
    pthread_mutex_t mutex;
   
    pthread_mutex_t *lmutex;
} thread_t;
typedef struct mutex_s
{
    pthread_mutex_t mtx;
} mutex_t;

int     ft_atoi(const char *str);
int check_arg(char *av[], int ac);

void *creat(void *philo);
long long calcultime();

void data(thread_t *thread, int i, char *av[], int ac);
void mutex_data(thread_t *thread);
#endif