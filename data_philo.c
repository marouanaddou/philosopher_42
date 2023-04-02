/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maddou <maddou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 14:10:07 by maddou            #+#    #+#             */
/*   Updated: 2023/04/02 23:17:27 by maddou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void time_usleep(int time)
{
    int i;

    i = 0;
    while(1)
    {
        if (i == time)
            break;
        usleep(200);
        i = i + 200;
    }
}

void  mutex_data(thread_t *thread)
{
    pthread_mutex_lock(&thread->mutex);
    pthread_mutex_lock(thread->lmutex);
    if (thread->die == 0)
    {
        printf("%lld %d has taken a fork\n", calcultime() - thread->start,  thread->i);
        thread->start_programe = calcultime();
        printf("%lld %d is eating\n",thread->start_programe  - thread->start, thread->i);
        usleep(1000 * thread->time_to_eat);
    }
    pthread_mutex_unlock(&thread->mutex);
    pthread_mutex_unlock(thread->lmutex);
    thread->cont_to_eat++;
    if (thread->die == 0)
    {
        printf("%lld %d is sleeping\n", calcultime() - thread->start, thread->i);
        // time_usleep(thread->time_to_sleep);
        usleep(1000 * thread->time_to_sleep);
    }
    if (thread->die == 0)
        printf("%lld %d is thinking\n", calcultime() - thread->start, thread->i);
}