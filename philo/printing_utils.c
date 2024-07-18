/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboukour <mboukour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 20:53:49 by mboukour          #+#    #+#             */
/*   Updated: 2024/07/18 22:23:29 by mboukour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_error(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(2, &str[i], 1);
		i++;
	}
}

int	print_thinking(t_philo *philo)
{
	t_program	*program;

	program = philo->program;
	pthread_mutex_lock(&program->print_lock);
	if (check_dead(program))
	{
		pthread_mutex_unlock(&program->print_lock);
		return (FALSE);
	}
	printf("%ld %d is thinking\n", get_timestamp(program),
		philo->philo_index + 1);
	pthread_mutex_unlock(&program->print_lock);
	return (TRUE);
}

int	print_sleeping(t_philo *philo)
{
	t_program	*program;

	program = philo->program;
	pthread_mutex_lock(&program->print_lock);
	if (check_dead(program))
	{
		pthread_mutex_unlock(&program->print_lock);
		return (FALSE);
	}
	printf("%ld %d is sleeping\n", get_timestamp(program),
		philo->philo_index + 1);
	pthread_mutex_unlock(&program->print_lock);
	ft_usleep(program->time_to_sleep, program);
	return (TRUE);
}

int	print_took_fork(t_philo *philo, int mode)
{
	t_program	*program;

	program = philo->program;
	pthread_mutex_lock(&program->print_lock);
	if (check_dead(program))
	{
		pthread_mutex_unlock(&program->print_lock);
		if (mode == RIGHT_FORK)
			pthread_mutex_unlock(philo->right_fork);
		else
		{
			pthread_mutex_unlock(philo->right_fork);
			pthread_mutex_unlock(philo->left_fork);
		}
		return (FALSE);
	}
	printf("%ld %d has taken a fork\n", get_timestamp(program),
		philo->philo_index + 1);
	pthread_mutex_unlock(&program->print_lock);
	if (philo->program->philo_count == 1 && !philo->left_fork)
		return (FALSE);
	return (TRUE);
}

int	print_eating(t_philo *philo)
{
	t_program	*program;

	program = philo->program;
	pthread_mutex_lock(&program->print_lock);
	if (check_dead(program))
		return (pthread_mutex_unlock(philo->right_fork),
			pthread_mutex_unlock(philo->left_fork),
			pthread_mutex_unlock(&program->print_lock), FALSE);
	printf("%ld %d is eating\n", get_timestamp(program),
		philo->philo_index + 1);
	pthread_mutex_unlock(&program->print_lock);
	pthread_mutex_lock(&philo->last_eat_lock);
	philo->last_eat = get_timestamp(program);
	pthread_mutex_unlock(&philo->last_eat_lock);
	ft_usleep(program->time_to_eat, program);
	limited_program(program, philo);
	return (pthread_mutex_unlock(philo->right_fork),
		pthread_mutex_unlock(philo->left_fork), TRUE);
}
