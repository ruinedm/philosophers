/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   observer_of_all.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboukour <mboukour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 08:22:11 by mboukour          #+#    #+#             */
/*   Updated: 2024/07/17 08:22:27 by mboukour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	something_happened(int status, t_program *program, int i)
{
	if (WIFEXITED(status))
	{
		if (WEXITSTATUS(status) == DEAD_PHILO)
		{
			kill_all(program, i);
			exit(EXIT_SUCCESS);
		}
		else if (WEXITSTATUS(status) == EATEN_ENOUGH)
			program->philos_done_eating++;
		else if (WEXITSTATUS(status) == EXIT_FAILURE)
		{
			kill_all(program, i);
			exit(EXIT_FAILURE);
		}
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
