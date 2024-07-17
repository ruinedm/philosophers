/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboukour <mboukour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 08:28:59 by mboukour          #+#    #+#             */
/*   Updated: 2024/07/17 12:20:24 by mboukour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

time_t	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) != 0)
		return (0);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

time_t	get_timestamp(t_program *program)
{
	return (get_time() - program->start_timestamp);
}

int	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = get_time();
	if (start == 0)
		return (-1);
	while ((get_time() - start) < milliseconds)
		usleep(500);
	return (0);
}

void	first_sems(t_program *program)
{
	sem_unlink("fork_sem");
	program->forks = sem_open("fork_sem", O_CREAT | O_EXCL, 0644,
			program->philo_count);
	if (program->forks == SEM_FAILED)
	{
		perror("sem_open");
		exit(EXIT_FAILURE);
	}
	sem_unlink("print_sem");
	program->print_sem = sem_open("print_sem", O_CREAT | O_EXCL, 0644, 1);
	if (program->forks == SEM_FAILED)
	{
		sem_close(program->forks);
		sem_unlink("fork_sem");
		perror("sem_open");
		exit(EXIT_FAILURE);
	}
}
