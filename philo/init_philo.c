/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboukour <mboukour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 22:07:14 by mboukour          #+#    #+#             */
/*   Updated: 2024/07/25 05:59:46 by mboukour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	link_forks(t_program *program)
{
	int		i;
	int		arr_size;
	t_philo	**philos_arr;

	i = 0;
	arr_size = program->philo_count;
	philos_arr = &(program->philos_arr);
	while (i < arr_size)
	{
		if (i == arr_size - 1 && i != 0)
			(*philos_arr)[i].left_fork = (*philos_arr)[0].right_fork;
		else if (i != arr_size)
			(*philos_arr)[i].left_fork = (*philos_arr)[i + 1].right_fork;
		i++;
	}
}

int	start_the_simulation(t_program *program)
{
	program->start_flag = FALSE;
	link_forks(program);
	if (!create_threads(program))
		return (FALSE);
	pthread_mutex_lock(&program->start_lock);
	program->start_flag = TRUE;
	pthread_mutex_unlock(&program->start_lock);
	if (!join_threads(program))
		return (FALSE);
	return (TRUE);
}

static int	init_philo_error(t_program *program, t_philo *philos_arr,
	int i, int error)
{
	clean_on_error(program, philos_arr, i);
	error_handler(error);
	return (FALSE);
}

static int	init_mutex_error(t_program *program, t_philo *philos_arr,
	int i, int type)
{
	free(philos_arr[i].right_fork);
	if (type == 0)
		return (init_philo_error(program, philos_arr, i, MUTEX_INIT_ERROR));
	pthread_mutex_destroy(&philos_arr[i].last_eat_lock);
	return (init_philo_error(program, philos_arr, i, MUTEX_INIT_ERROR));
}

int	init_philo(t_program *program)
{
	t_philo	*philos_arr;
	int		i;

	i = 0;
	philos_arr = malloc(sizeof(t_philo) * program->philo_count);
	if (!philos_arr)
		return (error_handler(MALLOC_ERROR),
			clean_all(program, CLEAN_PROGRAM), FALSE);
	while (i < program->philo_count)
	{
		philos_arr[i].program = program;
		philos_arr[i].philo_index = i;
		philos_arr[i].right_fork = malloc(sizeof(pthread_mutex_t));
		if (philos_arr[i].right_fork == NULL)
			return (init_philo_error(program, philos_arr, i, MALLOC_ERROR));
		philos_arr[i].last_eat = 0;
		philos_arr[i].i_ate = 0;
		if (pthread_mutex_init(&philos_arr[i].last_eat_lock, NULL))
			return (init_mutex_error(program, philos_arr, i, 0));
		if (pthread_mutex_init(philos_arr[i].right_fork, NULL))
			return (init_mutex_error(program, philos_arr, i, 1));
		i++;
	}
	program->philos_arr = philos_arr;
	return (start_the_simulation(program));
}
