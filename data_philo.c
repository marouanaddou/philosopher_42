/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maddou <maddou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 14:10:07 by maddou            #+#    #+#             */
/*   Updated: 2023/04/07 18:25:26 by maddou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	register_data(t_thread *thread, char *av[], int ac, t_mutex *mt)
{
	int	i;

	i = 0;
	while (i < ft_atoi(av[1]))
	{
		thread[i].number_of_philo = atoi(av[1]);
		thread[i].time_to_die = atoi(av[2]);
		thread[i].time_to_eat = atoi(av[3]);
		thread[i].time_to_sleep = atoi(av[4]);
		if (ac == 6)
			thread[i].number_eat = ft_atoi(av[5]);
		thread[i].start = calcultime();
		thread[i].start_programe = calcultime();
		thread[i].i = i + 1;
		thread[i].lmutex = &thread[(i + 1) % ft_atoi(av[1])].mutex;
		thread[i].mt = mt;
		thread[i].die = 0;
		thread[i].cont_to_eat = 0;
		pthread_create(&thread[i].th, NULL, &start_routine, &thread[i]);
		usleep(60);
		i++;
	}
}

void	time_usleep(int time)
{
	int			i;
	long long	start;

	i = 1;
	start = calcultime();
	while (1)
	{
		if (calcultime() - start >= time)
			break ;
		usleep(100);
	}
}

void	mutex_data(t_thread *thread)
{
	pthread_mutex_lock(&thread->mutex);
	pthread_mutex_lock(thread->lmutex);
	pthread_mutex_lock(&thread->mt->mut);
	if (thread->die == 0)
	{
		pthread_mutex_unlock(&thread->mt->mut);
		print("has taken a fork", thread);
		pthread_mutex_lock(&thread->mt->mut);
		thread->start_programe = calcultime();
		pthread_mutex_unlock(&thread->mt->mut);
		print("is eating", thread);
		time_usleep(thread->time_to_eat);
	}
	else
		pthread_mutex_unlock(&thread->mt->mut);
	pthread_mutex_unlock(&thread->mutex);
	pthread_mutex_unlock(thread->lmutex);
	pthread_mutex_lock(&thread->mt->mut);
	thread->cont_to_eat++;
	pthread_mutex_unlock(&thread->mt->mut);
	print_data(thread);
}
