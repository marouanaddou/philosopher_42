/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maddou <maddou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 12:16:16 by maddou            #+#    #+#             */
/*   Updated: 2023/05/05 21:09:48 by maddou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct mutex_s
{
	pthread_mutex_t	mut;
	int				die;
}					t_mutex;

typedef struct thread_s
{
	int				i;
	int				j;
	int				die;
	int				*return_thread;
	int				return_join;
	int				cont_to_eat;
	int				number_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_eat;
	long long		start;
	long long		start_programe;
	long long		timestamp;
	pthread_t		th;
	pthread_mutex_t	mutex;
	t_mutex			*mt;
	pthread_mutex_t	*lmutex;
}					t_thread;

int					ft_atoi(const char *str);
int					check_arg(char *av[], int ac);

void				*start_routine(void *philo);
long long			calcultime(void);

void				mutex_data(t_thread *thread);

void				register_data(t_thread *thread, char *av[], int ac,
						t_mutex *mt);

int					cont_eat(t_thread *thread);
int					check_die(t_thread *thread, char **av, int i);
void				time_usleep(int time);
void				print_data(t_thread *thread);

void				print(char *str, t_thread *thread);
#endif