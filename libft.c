/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maddou <maddou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 16:51:31 by maddou            #+#    #+#             */
/*   Updated: 2023/03/26 16:53:27 by maddou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int     ft_atoi(const char *str)
{
        int                     i;
        int                     sign;
        int                     nb;

        i = 0;
        sign = 1;
        nb = 0;
        while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
                i++;
        if (str[i] == '-')
        {
                sign *= -1;
                i++;
        }
        else if (str[i] == '+')
                i++;
        while (str[i] >= 48 && str[i] <= 57)
        {
                nb = nb * 10 + str[i] - 48;
                i++;
        }
        return (nb * sign);
}