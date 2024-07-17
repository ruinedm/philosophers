/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboukour <mboukour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 02:44:42 by mboukour          #+#    #+#             */
/*   Updated: 2024/07/17 08:23:42 by mboukour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_program	program;

	if (!parse_and_check(ac, av, &program))
		return (1);
	init_philo(&program);
	sem_close(program.forks);
	return (0);
}
