/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboukour <mboukour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 02:44:58 by mboukour          #+#    #+#             */
/*   Updated: 2024/07/17 02:45:00 by mboukour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	str_to_int(const char *str, int i, int sign, int *error_flag)
{
	unsigned long long	nb;
	int					count;

	nb = 0;
	count = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		count++;
		if (count == 11)
		{
			if (sign == -1)
				return (*error_flag = TRUE, 0);
			return (*error_flag = TRUE, -1);
		}
		nb = nb * 10 + str[i] - '0';
		i++;
	}
	if (nb > INT_MAX)
	{
		if (sign == -1)
			return (*error_flag = TRUE, 0);
		return (*error_flag = TRUE, -1);
	}
	return ((int)nb * sign);
}

int	ft_atoi(const char *str, int *error_flag)
{
	int		sign;
	size_t	i;

	sign = 1;
	i = 0;
	while (str[i] && (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13)))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] == '0')
		i++;
	return (str_to_int(str, i, sign, error_flag));
}
