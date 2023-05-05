/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maddou <maddou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 19:55:30 by maddou            #+#    #+#             */
/*   Updated: 2023/05/05 18:54:21 by maddou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	cont_eat(t_thread *thread)
{
	int	i;
	int	nb;

	i = 0;
	nb = 0;
	while (1)
	{
		if (thread[i].cont_to_eat == thread[i].number_eat)
			nb++;
		if (nb == thread[i].number_of_philo - 1)
			return (0);
		if (i == thread[i].number_of_philo - 1)
			break ;
		i++;
	}
	return (1);
}

void	print(char *str, t_thread *thread)
{
	pthread_mutex_lock(&thread->mt->mut);
	if (thread->mt->die == 0)
	{
		printf("%lld %d %s\n", calcultime() - thread->start, thread->i, str);
		pthread_mutex_unlock(&thread->mt->mut);
	}
	else
		pthread_mutex_unlock(&thread->mt->mut);
}

void	print_data(t_thread *thread)
{
	pthread_mutex_lock(&thread->mt->mut);
	if (thread->mt->die == 0)
	{
		pthread_mutex_unlock(&thread->mt->mut);
		print("is sleeping", thread);
		time_usleep(thread->time_to_sleep);
	}
	else
		pthread_mutex_unlock(&thread->mt->mut);
	pthread_mutex_lock(&thread->mt->mut);
	if (thread->mt->die == 0)
	{
		pthread_mutex_unlock(&thread->mt->mut);
		print("is thinking", thread);
	}
	else
		pthread_mutex_unlock(&thread->mt->mut);
}

int	check_die(t_thread *thread, char **av, int i)
{
	if (ft_atoi(av[1]) == 1)
		i = 0;
	pthread_mutex_lock(&thread[i].mt->mut);
	if (calcultime() - thread[i].start_programe >= ft_atoi(av[2]))
	{
		pthread_mutex_unlock(&thread[i].mt->mut);
		pthread_mutex_lock(&thread[i].mt->mut);
			thread[i].mt->die = 1;
		pthread_mutex_unlock(&thread[i].mt->mut);
		printf("%lld %d die\n", calcultime() - thread[i].start_programe, i + 1);
		return (0);
	}
	pthread_mutex_unlock(&thread[i].mt->mut);
	return (1);
}