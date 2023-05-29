/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maddou <maddou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 14:10:07 by maddou            #+#    #+#             */
/*   Updated: 2023/05/29 21:57:02 by maddou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
		thread[i].mtx = mtx;
		thread[i].start = mtx->time_start;
		thread[i].cont_to_eat = 0;
		if (pthread_create(&thread[i].th, NULL, &routine, &thread[i]) != 0)
			return (1);
		i++;
	}
	return (0);
}
