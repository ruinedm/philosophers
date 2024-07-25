/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboukour <mboukour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 02:44:42 by mboukour          #+#    #+#             */
/*   Updated: 2024/07/25 05:07:05 by mboukour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	init_routine_error(t_philo *philo, int type)
{
	sem_close(philo->last_eat_sem);
	sem_unlink(philo->last_eat_str);
	free(philo->last_eat_str);
	error_handler(type);
	exit(EXIT_FAILURE);
}

static int	init_routine(t_program *program, t_philo *philo)
{
	char	*str_index;
	char	*last_eat_str;

	str_index = ft_itoa(philo->philo_index);
	if (!str_index)
		return (error_handler(MALLOC_ERROR), exit(EXIT_FAILURE), 0);
	last_eat_str = ft_strjoin("last_eat_", str_index);
	if (!last_eat_str)
		return (free(str_index), error_handler(MALLOC_ERROR),
			exit(EXIT_FAILURE), 0);
	free(str_index);
	sem_unlink(last_eat_str);
	philo->last_eat_str = last_eat_str;
	philo->last_eat_sem = sem_open(last_eat_str, O_CREAT | O_EXCL, 0644, 1);
	if (philo->last_eat_sem == SEM_FAILED)
		return (perror("sem_open"), exit(EXIT_FAILURE), 0);
	philo->last_eat = get_timestamp(program);
	if (pthread_create(&philo->philo_observer, NULL, philo_observer_routine,
			(void *)philo) == -1)
		return (init_routine_error(philo, CREATE_THREAD_ERROR), 0);
	if (pthread_detach(philo->philo_observer) == -1)
		return (init_routine_error(philo, DETACH_THREAD_ERROR), 0);
	return (0);
}

void	philo_routine(t_philo *philo)
{
	t_program	*program;

	program = philo->program;
	init_routine(program, philo);
	while (TRUE)
	{
		pick_up_fork(program, philo);
		pick_up_fork(program, philo);
		sem_wait(philo->last_eat_sem);
		philo->last_eat = get_timestamp(program);
		sem_post(philo->last_eat_sem);
		philo->eat_count++;
		eat_and_put_down_forks(program, philo);
		if (program->is_limited && philo->eat_count >= program->number_of_eat)
		{
			sem_close(philo->last_eat_sem);
			sem_unlink(philo->last_eat_str);
			free(philo->last_eat_str);
			exit(EATEN_ENOUGH);
		}
		sleep_think_philo(program, philo);
	}
}

int	main(int ac, char **av)
{
	t_program	program;

	if (!parse_and_check(ac, av, &program))
		return (1);
	init_philo(&program);
	return (0);
}
