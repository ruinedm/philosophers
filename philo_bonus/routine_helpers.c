/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboukour <mboukour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 08:27:21 by mboukour          #+#    #+#             */
/*   Updated: 2024/07/17 12:20:56 by mboukour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	pick_up_fork(t_program *program, t_philo *philo)
{
	sem_wait(program->forks);
	sem_wait(program->print_sem);
	printf("%ld %i has taken a fork\n", get_timestamp(program),
		philo->philo_index + 1);
	sem_post(program->print_sem);
}

void	eat_and_put_down_forks(t_program *program, t_philo *philo)
{
	sem_wait(program->print_sem);
	printf("%ld %i is eating\n", get_timestamp(program),
		philo->philo_index + 1);
	sem_post(program->print_sem);
	ft_usleep(program->time_to_eat);
	sem_post(program->forks);
	sem_post(program->forks);
}

void	sleep_think_philo(t_program *program, t_philo *philo)
{
	sem_wait(program->print_sem);
	printf("%ld %d is sleeping\n", get_timestamp(program),
		philo->philo_index + 1);
	sem_post(program->print_sem);
	ft_usleep(program->time_to_sleep);
	sem_wait(program->print_sem);
	printf("%ld %i is thinking\n", get_timestamp(program),
		philo->philo_index + 1);
	sem_post(program->print_sem);
}
