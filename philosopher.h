/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maddou <maddou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 12:16:16 by maddou            #+#    #+#             */
/*   Updated: 2023/05/26 18:54:11 by maddou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# include <limits.h>

typedef struct mutex_s
{
	pthread_mutex_t	mut;
	long long time_start;
	pthread_mutex_t	eat;
	int				die;
}					t_mutex;


typedef struct thread_s
{
	int				i;
	int				die;
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
	pthread_mutex_t	*lmutex;
	t_mutex			*mt;
}					t_thread;

long long				ft_atoi(const char *str);
int						check_arg(char *av[], int ac);

void				*start_routine(void *philo);
long long			calcultime(void);

void				mutex_data(t_thread *thread);

int				register_data(t_thread *thread, char *av[], int ac,
						t_mutex *mtx);//

int					cont_eat(t_thread *thread);
int					check_die(t_thread *thread, char **av, int i);
void	time_usleep(int time);//
void				print_data(t_thread *thread);

void				print(char *str, t_thread *thread);

int 				check_range(char **av, int ac);
#endif