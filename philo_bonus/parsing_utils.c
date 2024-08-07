/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboukour <mboukour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 08:27:12 by mboukour          #+#    #+#             */
/*   Updated: 2024/07/25 04:13:05 by mboukour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_num(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+' || str[i] == '-')
	{
		i++;
		if (!str[i])
			return (FALSE);
	}
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (FALSE);
		i++;
	}
	return (TRUE);
}

int	is_pos_num(char *str)
{
	if (str[0] == '-')
		return (FALSE);
	return (TRUE);
}

int	is_valid_av(int ac, char **av)
{
	int	i;

	i = 1;
	while (i < ac)
	{
		if (!is_num(av[i]) || !is_pos_num(av[i]))
			return (FALSE);
		i++;
	}
	return (TRUE);
}

int	parse_settter(t_program *program, char **av, int *error_flag)
{
	program->philo_count = ft_atoi(av[1], error_flag);
	program->time_to_die = ft_atoi(av[2], error_flag);
	program->time_to_eat = ft_atoi(av[3], error_flag);
	program->time_to_sleep = ft_atoi(av[4], error_flag);
	if (!program->philo_count || !program->time_to_die
		|| !program->time_to_eat || !program->time_to_sleep || *error_flag)
		return (error_handler(INPUT_ERROR), FALSE);
	program->is_limited = FALSE;
	program->number_of_eat = -1;
	program->philos_done_eating = 0;
	program->start_timestamp = get_time();
	if (program->start_timestamp == 0)
		return (error_handler(TIME_ERROR), FALSE);
	return (TRUE);
}

int	parse_and_check(int ac, char **av, t_program *program)
{
	int	error_flag;

	error_flag = FALSE;
	if ((ac != 5 && ac != 6) || !is_valid_av(ac, av))
		return (error_handler(INPUT_ERROR), FALSE);
	if (!parse_settter(program, av, &error_flag))
		return (FALSE);
	if (ac == 6)
	{
		program->is_limited = TRUE;
		program->number_of_eat = ft_atoi(av[5], &error_flag);
		if (!program->number_of_eat || error_flag)
			return (error_handler(INPUT_ERROR), FALSE);
	}
	if (program->time_to_die >= program->philo_count * 10
		&& ft_abs(program->time_to_die
			- (program->time_to_eat + program->time_to_sleep)) == 1)
		program->observer_sleep = 0;
	else
		program->observer_sleep = 1000;
	return (TRUE);
}
