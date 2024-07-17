/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboukour <mboukour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 20:53:55 by mboukour          #+#    #+#             */
/*   Updated: 2024/07/17 14:41:24 by mboukour         ###   ########.fr       */
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

int	limited_program(t_program *program, t_philo *philo)
{
	if (program->is_limited == TRUE)
	{
		philo->i_ate++;
		if (philo->i_ate >= program->number_of_eat)
		{
			pthread_mutex_lock(&program->count_lock);
			program->eat_count++;
			pthread_mutex_unlock(&program->count_lock);
			pthread_mutex_unlock(philo->right_fork);
			pthread_mutex_unlock(philo->left_fork);
			return (0);
		}
	}
	return (1);
}
