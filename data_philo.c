/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maddou <maddou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 14:10:07 by maddou            #+#    #+#             */
/*   Updated: 2023/05/28 11:24:55 by maddou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	initialisation(t_thread *thread, int i, char *av[])
{
	thread[i].number_of_philo = atoi(av[1]);
	thread[i].time_to_die = atoi(av[2]);
	thread[i].time_to_eat = atoi(av[3]);
	thread[i].time_to_sleep = atoi(av[4]);
}

int	register_data(t_thread *thread, char *av[], int ac, t_mutex *mtx)
{
	int			i;

	i = 0;
	mtx->time_start = calcultime();
	while (i < ft_atoi(av[1]))
	{
		initialisation(thread, i, av);
		if (ac == 6)
			thread[i].number_eat = ft_atoi(av[5]);
		thread[i].start_programe = calcultime();
		thread[i].i = i + 1;
		thread[i].lmutex = &thread[(i + 1) % ft_atoi(av[1])].mutex;
		thread[i].mt = mtx;
		thread[i].start = mtx->time_start;
		thread[i].cont_to_eat = 0;
		if (pthread_create(&thread[i].th, NULL, &routine, &thread[i]) != 0)
			return (1);
		usleep(60);
		i++;
	}
	return (0);
}

void	time_usleep(int time)
{
	long long	start;

	start = calcultime();
	while (1)
	{
		if (calcultime() - start >= time)
			break ;
		usleep(60);
	}
}

void	ft_think(t_thread *thread)
{
	pthread_mutex_lock(&thread->mt->mut);
	if (thread->mt->die == 0)
	{
		pthread_mutex_unlock(&thread->mt->mut);
		print("is thinking", thread);
	}
	else
		pthread_mutex_unlock(&thread->mt->mut);
}

void	mutex_data(t_thread *thread)
{
	ft_think(thread);
	pthread_mutex_lock(&thread->mutex);
	pthread_mutex_lock(thread->lmutex);
	pthread_mutex_lock(&thread->mt->mut);
	if (thread->mt->die == 0)
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
