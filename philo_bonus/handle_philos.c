/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_philos.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboukour <mboukour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 08:21:26 by mboukour          #+#    #+#             */
/*   Updated: 2024/07/25 05:05:15 by mboukour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_observer_routine(void *void_philo)
{
	t_philo		*philo;
	t_program	*program;
	time_t		time;

	philo = (t_philo *)void_philo;
	program = philo->program;
	while (TRUE)
	{
		usleep(program->observer_sleep);
		sem_wait(philo->last_eat_sem);
		time = get_timestamp(program);
		if (time - philo->last_eat > program->time_to_die)
		{
			sem_wait(program->print_sem);
			printf("%ld %i has died\n", get_timestamp(program),
				philo->philo_index + 1);
			sem_close(philo->last_eat_sem);
			sem_unlink(philo->last_eat_str);
			free(philo->last_eat_str);
			exit(DEAD_PHILO);
		}
		sem_post(philo->last_eat_sem);
	}
	return (NULL);
}

static void	go_philo(t_program *program, int i)
{
	program->philos_arr[i].philo_index = i;
	program->philos_arr[i].eat_count = 0;
	program->philos_arr[i].program = program;
	program->philos_arr[i].last_eat = 0;
	program->philos_arr[i].eat_count = 0;
	program->philos_arr[i].philo_id = fork();
	if (program->philos_arr[i].philo_id == -1)
	{
		perror("fork:");
		kill_on_error(program, i);
		exit_procedure(EXIT_FAILURE, program);
	}
	else if (!program->philos_arr[i].philo_id)
		philo_routine(&program->philos_arr[i]);
}

void	init_philo(t_program *program)
{
	int		i;

	i = 0;
	program->philos_arr = malloc(sizeof(t_philo) * program->philo_count);
	if (!program->philos_arr)
	{
		error_handler(MALLOC_ERROR);
		exit(EXIT_FAILURE);
	}
	first_sems(program);
	while (i < program->philo_count)
	{
		go_philo(program, i);
		i++;
	}
	observe_philos(program);
}
