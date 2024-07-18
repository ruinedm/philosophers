/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboukour <mboukour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 21:26:13 by mboukour          #+#    #+#             */
/*   Updated: 2024/07/18 21:38:45 by mboukour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	parse_arguments(int ac, char **av, t_program *program)
{
	int	error_flag;

	error_flag = FALSE;
	if ((ac != 5 && ac != 6) || !is_valid_av(ac, av))
		return (error_handler(INPUT_ERROR), FALSE);
	program->philo_count = ft_atoi(av[1], &error_flag);
	program->time_to_die = ft_atoi(av[2], &error_flag);
	program->time_to_eat = ft_atoi(av[3], &error_flag);
	program->time_to_sleep = ft_atoi(av[4], &error_flag);
	if (ac == 6)
	{
		program->is_limited = TRUE;
		program->number_of_eat = ft_atoi(av[5], &error_flag);
	}
	else
	{
		program->is_limited = FALSE;
		program->number_of_eat = -1;
	}
	if (error_flag)
		return (error_handler(INPUT_ERROR), FALSE);
	return (TRUE);
}

int	initialize_program(t_program *program)
{
	if (!program->philo_count || !program->time_to_die || !program->time_to_eat
		|| !program->time_to_sleep || !program->number_of_eat)
		return (error_handler(INPUT_ERROR), FALSE);
	program->eat_count = 0;
	program->start_timestamp = get_time();
	if (program->start_timestamp == 0)
		return (error_handler(TIME_ERROR), FALSE);
	program->is_locked = FALSE;
	program->dead_flag = FALSE;
	return (initialize_mutexes(program));
}

int	parse_and_check(int ac, char **av, t_program *program)
{
	if (!parse_arguments(ac, av, program))
		return (FALSE);
	return (initialize_program(program));
}
