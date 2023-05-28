/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maddou <maddou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 17:37:35 by maddou            #+#    #+#             */
/*   Updated: 2023/05/28 16:18:42 by maddou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

long long	calcultime(void)
{
	long long		time;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (time);
}

void	*routine(void *philo)
{
	t_thread	*thread;

	thread = (t_thread *)philo;
	while (1)
		mutex_data(thread);
	return (0);
}

int	creat_philosopher(t_thread *thread, char *av[], int ac, t_mutex *mtx)
{
	int	i;

	if (register_data(thread, av, ac, mtx) != 0)
		return (0);
	i = 0;
	while (1)
	{
		if (check_die(thread, av, i) == 0)
			break ;
		pthread_mutex_lock(&thread->mt->mut);
		if (ac == 6)
		{
			if (cont_eat(thread) == 0 && ft_atoi(av[1]) != 1)
			{
				pthread_mutex_unlock(&thread->mt->mut);
				break ;
			}
		}
		pthread_mutex_unlock(&thread->mt->mut);
		i++;
		if (i == ft_atoi(av[1]) - 1)
			i = 0;
	}	
	return (1);
}

int	creat_mutex(t_thread *thread, char **av, int i, t_mutex *mtx)
{
	while (i < ft_atoi(av[1]))
	{
		if (pthread_mutex_init(&thread[i++].mutex, NULL) != 0)
			return (1);
	}
	if (pthread_mutex_init(&mtx->mut, NULL) != 0)
		return (1);
	return (0);
}

int	main(int ac, char *av[])
{
	t_thread		thread[250];
	t_mutex			mtx;
	int				i;

	i = 0;
	mtx.die = 0;
	if (ac == 5 || ac == 6)
	{
		if (check_arg(av, ac) == 0 || ft_atoi(av[1]) > 200)
			return (0);
		if (creat_mutex(thread, av, i, &mtx) != 0)
			return (0);
		if (creat_philosopher(thread, av, ac, &mtx) != 0)
			return (0);
		i = 0;
		while (i < ft_atoi(av[1]))
		{
			if (pthread_mutex_destroy(&thread[i++].mutex) != 0)
				return (0);
		}
		if (pthread_mutex_destroy(&mtx.mut) != 0)
			return (0);
	}
	return (0);
}
