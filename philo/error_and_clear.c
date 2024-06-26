/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_and_clear.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboukour <mboukour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 21:04:56 by mboukour          #+#    #+#             */
/*   Updated: 2024/06/26 21:20:54 by mboukour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	clean_program(t_program *program)
{
	pthread_mutex_destroy(&program->print_lock);
	pthread_mutex_destroy(&program->dead_lock);
	if (program->is_limited == TRUE)
		pthread_mutex_destroy(&program->count_lock);
}

static void	clean_philos(t_program *program)
{
	int	i;

	i = 0;
	while (i < program->philo_count)
	{
		pthread_mutex_destroy(&program->philos_arr[i].last_eat_lock);
		pthread_mutex_destroy(program->philos_arr[i].right_fork);
		free(program->philos_arr[i].right_fork);
		i++;
	}
	free(program->philos_arr);
}

void	clean_all(t_program *program, int mode)
{
	int	i;

	i = 0;
	if (mode == CLEAN_ALL)
	{
		clean_philos(program);
		clean_program(program);
	}
	else if (mode == CLEAN_PROGRAM)
		clean_program(program);
}

void	clean_on_error(t_program *program, t_philo *philos_arr, int current,
	int mode)
{
	int	i;

	i = 0;
	while (i < current)
	{
		pthread_mutex_destroy(&philos_arr[i].last_eat_lock);
		pthread_mutex_destroy(philos_arr[i].right_fork);
		free(philos_arr[i].right_fork);
		i++;
	}
	free(philos_arr);
	clean_all(program, CLEAN_PROGRAM);
}

void	error_handler(int mode)
{
	if (mode == INPUT_ERROR)
		print_error("Error: Invalid input!\n");
	else if (mode == TIME_ERROR)
		print_error("Error: Could not retrieve current time!\n");
	else if (mode == MALLOC_ERROR)
		print_error("Error: Could not allocate memory!\n");
	else if (mode == CREATE_THREAD_ERROR)
		print_error("Error: Could not create thread!\n");
	else if (mode == JOIN_THREAD_ERROR)
		print_error("Error: Could not join thread!\n");
	else if (mode == MUTEX_INIT_ERROR)
		print_error("Error: Could not initialize mutex!\n");
}

void	join_on_error(t_program *program, int current)
{
	int	i;

	i = 0;
	while (i < current)
	{
		pthread_join(program->philos_arr[i].philo_id, NULL);
		i++;
	}
}
