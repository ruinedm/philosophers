/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboukour <mboukour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 20:53:35 by mboukour          #+#    #+#             */
/*   Updated: 2024/07/25 04:13:05 by mboukour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_num(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+' || str[i] == '-')
	{
		i++;
		if (!str[i])
			return (FALSE);
	}
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (FALSE);
		i++;
	}
	return (TRUE);
}

int	is_pos_num(char *str)
{
	if (str[0] == '-')
		return (FALSE);
	return (TRUE);
}

int	is_valid_av(int ac, char **av)
{
	int	i;

	i = 1;
	while (i < ac)
	{
		if (!is_num(av[i]) || !is_pos_num(av[i]))
			return (FALSE);
		i++;
	}
	return (TRUE);
}

int	initialize_mutexes(t_program *program)
{
	if (pthread_mutex_init(&program->print_lock, NULL))
		return (error_handler(MUTEX_INIT_ERROR), FALSE);
	if (pthread_mutex_init(&program->dead_lock, NULL))
		return (pthread_mutex_destroy(&program->print_lock),
			error_handler(MUTEX_INIT_ERROR), FALSE);
	if (pthread_mutex_init(&program->start_lock, NULL))
		return (pthread_mutex_destroy(&program->print_lock),
			pthread_mutex_destroy(&program->dead_lock),
			error_handler(MUTEX_INIT_ERROR), FALSE);
	if (program->is_limited)
	{
		if (pthread_mutex_init(&program->count_lock, NULL))
		{
			pthread_mutex_destroy(&program->print_lock);
			pthread_mutex_destroy(&program->dead_lock);
			pthread_mutex_destroy(&program->start_lock);
			return (FALSE);
		}
	}
	return (TRUE);
}
