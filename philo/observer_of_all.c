/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   observer_of_all.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboukour <mboukour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 20:54:56 by mboukour          #+#    #+#             */
/*   Updated: 2024/07/17 00:13:52 by mboukour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_dead(t_program *program)
{
	pthread_mutex_lock(&program->dead_lock);
	if (program->dead_flag)
	{
		pthread_mutex_unlock(&program->dead_lock);
		return (TRUE);
	}
	pthread_mutex_unlock(&program->dead_lock);
	return (FALSE);
}

void	set_as_dead(t_program *program)
{
	pthread_mutex_lock(&program->dead_lock);
	program->dead_flag = TRUE;
	pthread_mutex_unlock(&program->dead_lock);
}

int	is_dead(t_program *program, t_philo *philo, int i)
{
	pthread_mutex_lock(&philo->last_eat_lock);
	if (get_timestamp(program) - philo->last_eat > program->time_to_die)
	{
		pthread_mutex_unlock(&philo->last_eat_lock);
		pthread_mutex_lock(&program->print_lock);
		printf("%ld %d died\n", get_timestamp(program), i + 1);
		set_as_dead(program);
		pthread_mutex_unlock(&program->print_lock);
		return (TRUE);
	}
	pthread_mutex_unlock(&philo->last_eat_lock);
	return (FALSE);
}

int	is_done_eating(t_program *program)
{
	if (program->is_limited == TRUE)
	{
		pthread_mutex_lock(&program->count_lock);
		if (program->eat_count >= program->philo_count * program->number_of_eat)
		{
			pthread_mutex_unlock(&program->count_lock);
			pthread_mutex_lock(&program->print_lock);
			set_as_dead(program);
			pthread_mutex_unlock(&program->print_lock);
			return (TRUE);
		}
		pthread_mutex_unlock(&program->count_lock);
	}
	return (FALSE);
}

void	*observer_of_all(void *void_program)
{
	t_program	*program;
	int			i;

	program = (t_program *)void_program;
	while (TRUE)
	{
		i = 0;
		while (i < program->philo_count)
		{
			if (is_dead(program, &program->philos_arr[i], i))
				return (NULL);
			if (is_done_eating(program))
				return (NULL);
			i++;
		}
	}
	return (NULL);
}
