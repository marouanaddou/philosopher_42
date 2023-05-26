/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maddou <maddou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 18:06:41 by maddou            #+#    #+#             */
/*   Updated: 2023/05/24 20:13:31 by maddou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	check_number(int ac, char *av[])
{
	int	number_of_philo;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	number_eat;

	number_of_philo = ft_atoi(av[1]);
	time_to_die = ft_atoi(av[2]);
	time_to_eat = ft_atoi(av[3]);
	time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
	{
		number_eat = ft_atoi(av[5]);
		if (number_eat <= 0)
			return (0);
	}
	if (number_of_philo <= 0
		|| time_to_eat <= 0 || time_to_die <= 0
		|| time_to_sleep <= 0)
		return (0);
	return (1);
}

int	check_range(char **av, int ac)
{
	int	i;

	i = 1;
	while (i < ac)
	{
		if (ft_atoi(av[i]) > INT_MAX)
			return (0);
		i++;
	}
	return (1);
}

int	check_arg(char *av[], int ac)
{
	int	i;
	int	j;

	i = 1;
	while (i < ac)
	{
		j = 0;
		while (av[i][j] != '\0')
		{
			if (!(av[i][j] >= '0' && av[i][j] <= '9'))
			{
				printf("error\n");
				return (0);
			}
			j++;
		}
		i++;
	}
	if (check_number(ac, av) == 0 || check_range(av, ac) == 0)
	{
		printf("error\n");
		return (0);
	}	
	return (1);
}
