/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboukour <mboukour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 20:53:55 by mboukour          #+#    #+#             */
/*   Updated: 2024/06/26 22:03:14 by mboukour         ###   ########.fr       */
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

int	ft_usleep(size_t milliseconds, t_program *program)
{
	size_t	start;

	start = get_time();
	if (start == 0)
		return (-1);
	while ((get_time() - start) < milliseconds)
	{
		usleep(500);
		if (check_dead(program))
			return (0);
	}
	return (0);
}
