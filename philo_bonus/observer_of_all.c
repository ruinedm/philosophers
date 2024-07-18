/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   observer_of_all.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboukour <mboukour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 08:22:11 by mboukour          #+#    #+#             */
/*   Updated: 2024/07/18 21:42:38 by mboukour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	exit_procedure(int status, t_program *program)
{
	int	i;

	i = 0;
	free(program->philos_arr);
	sem_close(program->forks);
	sem_unlink("fork_sem");
	sem_close(program->print_sem);
	sem_unlink("print_sem");
	exit(status);
}

void	something_happened(int status, t_program *program, int i)
{
	if (WIFEXITED(status))
	{
		if (WEXITSTATUS(status) == DEAD_PHILO)
		{
			kill_all(program, i);
			exit_procedure(EXIT_SUCCESS, program);
		}
		else if (WEXITSTATUS(status) == EATEN_ENOUGH)
			program->philos_done_eating++;
		else if (WEXITSTATUS(status) == EXIT_FAILURE)
		{
			kill_all(program, i);
			exit_procedure(EXIT_FAILURE, program);
		}
	}
	else if (WIFSIGNALED(status))
	{
		print_error("One of the simulation's processes (a philosopher) ");
		print_error("has received an external signal, ");
		print_error("the program will terminate now.");
		kill_on_error(program, program->philo_count);
		exit_procedure(EXIT_FAILURE, program);
	}
}

void	observe_philos(t_program *program)
{
	int		i;
	int		status;

	while (TRUE)
	{
		i = 0;
		while (i < program->philo_count)
		{
			if (waitpid(program->philos_arr[i].philo_id, &status, WNOHANG) > 0)
				something_happened(status, program, i);
			if (program->is_limited
				&& program->philos_done_eating == program->philo_count)
				exit(EXIT_SUCCESS);
			i++;
		}
	}
}
