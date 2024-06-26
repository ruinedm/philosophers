/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboukour <mboukour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 20:53:28 by mboukour          #+#    #+#             */
/*   Updated: 2024/06/26 22:06:32 by mboukour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	should_i_start(t_program *program)
{
	pthread_mutex_lock(&program->start_lock);
	if (program->start_flag)
	{
		pthread_mutex_unlock(&program->start_lock);
		return (FALSE);
	}
	pthread_mutex_unlock(&program->start_lock);
	return (TRUE);
}

int	philo_loop(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	if (!print_took_fork(philo, RIGHT_FORK))
		return (0);
	pthread_mutex_lock(philo->left_fork);
	if (!print_took_fork(philo, LEFT_FORK))
		return (0);
	if (!print_eating(philo) || !print_sleeping(philo)
		|| !print_thinking(philo))
		return (0);
	return (1);
}

void	*philo_routine(void *void_philo)
{
	t_philo		*philo;
	t_program	*program;

	philo = (t_philo *)void_philo;
	program = philo->program;
	while (TRUE)
	{
		if (!should_i_start(program))
			break ;
		if (check_dead(program))
			return (NULL);
	}
	if (philo->philo_index % 2 == 0)
		ft_usleep(program->time_to_eat / 2, program);
	while (TRUE)
	{
		if (!philo_loop(philo))
			break ;
	}
	return (NULL);
}
int		init_philo(t_program *program);

int	main(int ac, char **av)
{
	t_program	program;

	if (!parse_and_check(ac, av, &program))
		return (1);
	if (!init_philo(&program))
		return (1);
	clean_all(&program, CLEAN_ALL);
	return (0);
}
