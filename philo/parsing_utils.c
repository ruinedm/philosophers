#include "philo.h"

t_bool is_num(char *str)
{
	int i;

	i = 0;
	if(str[i] == '+' || str[i] == '-')
	{
		i++;
		if(!str[i])
			return (FALSE);
	}
	while(str[i])
	{
		if(str[i] < '0' || str[i] > '9')
			return (FALSE);
		i++;
	}
	return (TRUE);
}

t_bool is_pos_num(char *str)
{
	if(str[0] == '-')
		return (FALSE);
	return (TRUE);
}

t_bool is_valid_av(int ac,char **av)
{
	int i;

	i = 1;
	while(i < ac - 1)
	{
		if(!is_num(av[i]) || !is_pos_num(av[i]))
			return (FALSE);
		i++;
	}
	if(ac == 6 && !is_num(av[ac - 1]))
		return (FALSE);
	return (TRUE);
}

void parse_and_check(int ac, char **av, t_program *original)
{
	int i;

	if((ac != 5 && ac != 6) || !is_valid_av(ac, av))
		error_handler(INPUT_ERROR);
	original->philo_count = ft_atoi(av[1]);
	original->time_to_die = ft_atoi(av[2]);
	original->time_to_eat = ft_atoi(av[3]);
	original->time_to_sleep = ft_atoi(av[4]);
	original->is_limited = FALSE;
	original->is_first_run = TRUE;
	original->number_of_eat = -1;
	original->start_timestamp = get_time();
	original->is_locked = FALSE;
	original->dead_flag = FALSE;
	if(ac == 6)
	{
		original->is_limited = TRUE;
		original->number_of_eat = ft_atoi(av[5]);
	}
}
