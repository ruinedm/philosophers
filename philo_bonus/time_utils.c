/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboukour <mboukour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 08:28:59 by mboukour          #+#    #+#             */
/*   Updated: 2024/07/17 08:29:23 by mboukour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

time_t	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) != 0)
		return (0);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

time_t	get_timestamp(t_program *program)
{
	return (get_time() - program->start_timestamp);
}

int	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = get_time();
	if (start == 0)
		return (-1);
	while ((get_time() - start) < milliseconds)
		usleep(500);
	return (0);
}
