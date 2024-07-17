/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_philos.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboukour <mboukour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 08:21:26 by mboukour          #+#    #+#             */
/*   Updated: 2024/07/17 08:21:35 by mboukour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*philo_observer_routine(void *void_philo)
{
	t_philo		*philo;
	t_program	*program;
	time_t		time;

	philo = (t_philo *)void_philo;
	program = philo->program;
	while (TRUE)
	{
		usleep(1000);
		sem_wait(philo->last_eat_sem);
		time = get_timestamp(program);
		if (time - philo->last_eat > program->time_to_die)
		{
			sem_wait(program->print_sem);
			printf("%ld %i has died", get_timestamp(program),
				philo->philo_index + 1);
			exit(DEAD_PHILO);
		}
		sem_post(philo->last_eat_sem);
	}
	return (NULL);
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
	free(last_eat_str);
	sem_unlink(last_eat_str);
	philo->last_eat_sem = sem_open(last_eat_str, O_CREAT | O_EXCL, 0644, 1);
	if (philo->last_eat_sem == SEM_FAILED)
		return (perror("sem_open"), exit(EXIT_FAILURE), 0);
	philo->last_eat = get_timestamp(program);
	pthread_create(&philo->philo_observer, NULL, philo_observer_routine,
		(void *)philo);
	pthread_detach(philo->philo_observer);
	return (0);
}

static void	philo_routine(t_philo *philo)
{
	char		*philo_index;
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
			exit(EATEN_ENOUGH);
		sleep_think_philo(program, philo);
	}
	exit(EXIT_SUCCESS);
}

static void	go_philo(t_program *program, int i)
{
	program->philos_arr[i].philo_index = i;
	program->philos_arr[i].eat_count = 0;
	program->philos_arr[i].program = program;
	program->philos_arr[i].philo_id = fork();
	program->philos_arr[i].last_eat = 0;
	if (!program->philos_arr[i].philo_id)
		philo_routine(&program->philos_arr[i]);
}

void	init_philo(t_program *program)
{
	pid_t	pid;
	int		i;

	i = 0;
	program->philos_arr = malloc(sizeof(t_philo) * program->philo_count);
	if (!program->philos_arr)
		error_handler(MALLOC_ERROR);
	sem_unlink("fork_semaphore");
	program->forks = sem_open("fork_semaphore", O_CREAT | O_EXCL, 0644,
			program->philo_count);
	sem_unlink("print_sem");
	program->print_sem = sem_open("print_sem", O_CREAT | O_EXCL, 0644, 1);
	if (program->forks == SEM_FAILED)
	{
		perror("sem_open");
		exit(EXIT_FAILURE);
	}
	while (i < program->philo_count)
	{
		go_philo(program, i);
		i++;
	}
	observe_philos(program);
}
