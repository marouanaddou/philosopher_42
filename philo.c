/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maddou <maddou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 19:55:30 by maddou            #+#    #+#             */
/*   Updated: 2023/05/29 21:26:44 by maddou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	print(char *str, t_thread *thread)
{
	pthread_mutex_lock(&thread->mtx->mut);
	if (thread->mtx->died == 0)
	{
		printf("%lld %d %s\n", calcultime() - thread->start, thread->i, str);
		pthread_mutex_unlock(&thread->mtx->mut);
	}
	else
	{		
		pthread_mutex_unlock(&thread->mtx->mut);
		return (1);
	}
	return (0);
}

int	print_data(t_thread *thread)
{
	pthread_mutex_lock(&thread->mtx->mut);
	if (thread->mtx->died == 0)
	{
		pthread_mutex_unlock(&thread->mtx->mut);
		if (print("is sleeping", thread) == 1)
			return (1);
		if (time_usleep(thread->time_to_sleep, thread) == 1)
			return (1);
	}
	else
	{
		pthread_mutex_unlock(&thread->mtx->mut);
		return (1);
	}
	return (0);
}

int	ft_think(t_thread *thread)
{
	pthread_mutex_lock(&thread->mtx->mut);
	if (thread->mtx->died == 0)
	{
		pthread_mutex_unlock(&thread->mtx->mut);
		if (print("is thinking", thread) == 1)
			return (1);
	}
	else
	{
		pthread_mutex_unlock(&thread->mtx->mut);
		return (1);
	}
	return (0);
}

int	eating(t_thread *thread)
{
	if (thread->mtx->died == 0)
	{
		pthread_mutex_unlock(&thread->mtx->mut);
		if (print("has taken a fork", thread) == 1)
			return (1);
		pthread_mutex_lock(&thread->mtx->mut);
		thread->start_programe = calcultime();
		pthread_mutex_unlock(&thread->mtx->mut);
		if (print("is eating", thread) == 1)
			return (1);
		if (time_usleep(thread->time_to_eat, thread) == 1)
			return (1);
	}
	else
		pthread_mutex_unlock(&thread->mtx->mut);
	return (0);
}

int	mutex_data(t_thread *thread)
{
	if (ft_think(thread) == 1)
		return (1);
	pthread_mutex_lock(&thread->mutex);
	pthread_mutex_lock(thread->lmutex);
	pthread_mutex_lock(&thread->mtx->mut);
	if (eating(thread) == 1)
		return (1);
	pthread_mutex_unlock(&thread->mutex);
	pthread_mutex_unlock(thread->lmutex);
	pthread_mutex_lock(&thread->mtx->mut);
	thread->cont_to_eat++;
	pthread_mutex_unlock(&thread->mtx->mut);
	if (print_data(thread) == 1)
		return (1);
	return (0);
}
