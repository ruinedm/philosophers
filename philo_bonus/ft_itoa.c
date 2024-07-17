/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboukour <mboukour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 08:29:43 by mboukour          #+#    #+#             */
/*   Updated: 2024/07/17 08:29:44 by mboukour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	numlen(int n)
{
	int	len;

	len = 0;
	if (n <= 0)
		len++;
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

static void	fill_str(char *str, long nbr, int len)
{
	int	index;

	index = len - 1;
	if (nbr == 0)
		str[0] = '0';
	if (nbr < 0)
	{
		str[0] = '-';
		nbr = -nbr;
	}
	while (nbr != 0)
	{
		str[index--] = (nbr % 10) + '0';
		nbr /= 10;
	}
}

char	*ft_itoa(int n)
{
	long	nbr;
	int		len;
	char	*str;

	nbr = n;
	len = numlen(nbr);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	str[len] = '\0';
	fill_str(str, nbr, len);
	return (str);
}
