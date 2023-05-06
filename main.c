/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maddou <maddou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 17:37:35 by maddou            #+#    #+#             */
/*   Updated: 2023/05/06 16:52:47 by maddou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"
#include <pthread.h>

long long	calcultime(void)
{
	long long		time;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (time);
}

void	*start_routine(void *philo)
{
	t_thread	*thread;

	thread = (t_thread *)philo;
	while (1)
		mutex_data(thread);
	return (0);
}

void	creat_philosopher(t_thread *thread, char *av[], int ac, t_mutex *mt)
{
	int	i;

	register_data(thread, av, ac, mt);
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
		if (i == ft_atoi(av[1]) - 1)
			i = 0;
		i++;
	}
	i = 0;
	while (i < ft_atoi(av[1]) - 1)
		pthread_detach(thread[i++].th);
}

int	main(int ac, char *av[])
{
	t_thread		thread[250];
	t_mutex			mt;
	int				i;

	i = 0;
	mt.die = 0;
	if (ac == 5 || ac == 6)
	{
		if (check_arg(av, ac) == 0)
			return (0);
		while (i < ft_atoi(av[1]))
			pthread_mutex_init(&thread[i++].mutex, NULL);
		pthread_mutex_init(&mt.mut, NULL);
		creat_philosopher(thread, av, ac, &mt);
		i = 0;
		while(i < ft_atoi(av[1]))
			pthread_mutex_destroy(&thread[i++].mutex);
	}
}
