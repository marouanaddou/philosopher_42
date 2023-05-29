/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maddou <maddou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 21:33:39 by maddou            #+#    #+#             */
/*   Updated: 2023/05/29 21:57:26 by maddou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	calcultime(void)
{
	long long		time;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (time);
}

int	time_usleep(int time, t_thread *thread)
{
	long long	start;

	start = calcultime();
	while (1)
	{
		pthread_mutex_lock(&thread->mtx->mut);
		if (thread->mtx->died == 1)
		{
			pthread_mutex_unlock(&thread->mtx->mut);
			return (1);
		}
		pthread_mutex_unlock(&thread->mtx->mut);
		if (calcultime() - start >= time)
			break ;
		usleep(60);
	}
	return (0);
}

int	cont_eat(t_thread *thread)
{
	int	i;
	int	nb;

	i = 0;
	nb = 0;
	while (1)
	{
		if (thread[i].cont_to_eat >= thread[i].number_eat)
			nb++;
		if (nb == thread[i].number_of_philo)
			return (0);
		if (i == thread[i].number_of_philo - 1)
			break ;
		i++;
	}
	return (1);
}

int	check_die(t_thread *thread, char **av, int i)
{
	if (ft_atoi(av[1]) == 1)
		i = 0;
	pthread_mutex_lock(&thread[i].mtx->mut);
	if (calcultime() - thread[i].start_programe >= ft_atoi(av[2]))
	{
		pthread_mutex_unlock(&thread[i].mtx->mut);
		pthread_mutex_lock(&thread[i].mtx->mut);
		thread[i].mtx->died = 1;
		printf("%lld %d died\n", calcultime() - thread[i].start_programe, i + 1);
		pthread_mutex_unlock(&thread[i].mtx->mut);
		return (0);
	}
	pthread_mutex_unlock(&thread[i].mtx->mut);
	return (1);
}
