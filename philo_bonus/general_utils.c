/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboukour <mboukour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 08:28:39 by mboukour          #+#    #+#             */
/*   Updated: 2024/07/25 04:32:25 by mboukour         ###   ########.fr       */
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
	else if (mode == DETACH_THREAD_ERROR)
		print_error("Error: Could not detach thread!\n");
	else if (mode == MUTEX_INIT_ERROR)
		print_error("Error: Could not initialize mutex!\n");
}

void	clean_all(t_program *program)
{
	int	i;

	i = 0;
	while (i < program->philo_count)
	{
		free(&program->philos_arr[i]);
		i++;
	}
	free(program->philos_arr);
}

void	kill_all(t_program *program, int already_dead)
{
	int	i;

	i = 0;
	while (i < program->philo_count)
	{
		if (i != already_dead)
			kill(program->philos_arr[i].philo_id, SIGKILL);
		i++;
	}
}

void	kill_on_error(t_program *program, int until)
{
	int	i;

	i = 0;
	while (i < until)
	{
		kill(program->philos_arr[i].philo_id, SIGKILL);
		i++;
	}
}
