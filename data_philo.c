/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maddou <maddou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 14:10:07 by maddou            #+#    #+#             */
/*   Updated: 2023/04/04 17:01:35 by maddou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"
#include <pthread.h>

void time_usleep(int time)
{
    int i;
    pthread_mutex_t mt;

    i = 0;
    pthread_mutex_lock(&mt);
    while(1)
    {
        if (i == time)
            break;
        usleep(200);
        i = i + 200;
    }
    pthread_mutex_unlock(&mt);
}

void  mutex_data(thread_t *thread)
{
    pthread_mutex_lock(&thread->mutex);
    pthread_mutex_lock(thread->lmutex);
    pthread_mutex_lock(&thread->mt->mut);
    if (thread->die == 0)
    {
        pthread_mutex_unlock(&thread->mt->mut);
        printf("%lld %d has taken a fork\n", calcultime() - thread->start,  thread->i);    
        pthread_mutex_lock(&thread->mt->mut);
            thread->start_programe = calcultime();
        pthread_mutex_unlock(&thread->mt->mut);
        printf("%lld %d is eating\n",thread->start_programe  - thread->start, thread->i);
        usleep(1000 * thread->time_to_eat);
    }
    pthread_mutex_unlock(&thread->mutex);
    pthread_mutex_unlock(thread->lmutex);
        
    pthread_mutex_lock(&thread->mt->mut);
        thread->cont_to_eat++;
    pthread_mutex_unlock(&thread->mt->mut);
    
    pthread_mutex_lock(&thread->mt->mut);
    if (thread->die == 0)
    {
        pthread_mutex_unlock(&thread->mt->mut);
        printf("%lld %d is sleeping\n", calcultime() - thread->start, thread->i);
        usleep(1000 * thread->time_to_sleep);
    }
    pthread_mutex_lock(&thread->mt->mut);
    if (thread->die == 0)
        printf("%lld %d is thinking\n", calcultime() - thread->start, thread->i);
    pthread_mutex_unlock(&thread->mt->mut);
    
}