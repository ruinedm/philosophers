/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboukour <mboukour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 16:02:31 by mboukour          #+#    #+#             */
/*   Updated: 2024/07/16 05:07:46 by mboukour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	create_thread_error(t_program *program, int i)
{
	set_as_dead(program);
	join_on_error(program, i);
	error_handler(CREATE_THREAD_ERROR);
	clean_all(program, CLEAN_ALL);
}

int	create_threads(t_program *program)
{
	int		i;
	int		arr_size;
	t_philo	**philos_arr;

	i = 0;
	arr_size = program->philo_count;
	philos_arr = &(program->philos_arr);
	while (i < arr_size)
	{
		if (pthread_create(&(*philos_arr)[i].philo_id,
			NULL, philo_routine, &(*philos_arr)[i]))
			return (create_thread_error(program, i), FALSE);
		i++;
	}
	if (pthread_create(&program->observer_id, NULL, observer_of_all, program))
		return (create_thread_error(program, i), FALSE);
	return (TRUE);
}

int	join_threads(t_program *program)
{
	int		i;
	int		arr_size;
	t_philo	**philos_arr;

	i = 0;
	arr_size = program->philo_count;
	philos_arr = &(program->philos_arr);
	while (i < arr_size)
	{
		if (pthread_join((*philos_arr)[i].philo_id, NULL))
			return (set_as_dead(program), error_handler(CREATE_THREAD_ERROR),
				clean_all(program, CLEAN_ALL), FALSE);
		i++;
	}
	if (pthread_join(program->observer_id, NULL))
		return (set_as_dead(program), error_handler(CREATE_THREAD_ERROR),
			clean_all(program, CLEAN_ALL), FALSE);
	return (TRUE);
}
