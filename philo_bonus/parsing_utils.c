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
	while(i < ac)
	{
		if(!is_num(av[i]) || !is_pos_num(av[i]))
			return (FALSE);
		i++;
	}
	return (TRUE);
}



int parse_and_check(int ac, char **av, t_program *program) 
{
    if((ac != 5 && ac != 6) || !is_valid_av(ac, av))
        return (error_handler(INPUT_ERROR), FALSE);
    program->philo_count = ft_atoi(av[1]);
    program->time_to_die = ft_atoi(av[2]);
    program->time_to_eat = ft_atoi(av[3]);
    program->time_to_sleep = ft_atoi(av[4]);
    if(!program->philo_count || !program->time_to_die || !program->time_to_eat || !program->time_to_sleep)
        return (error_handler(INPUT_ERROR), FALSE);
    program->is_limited = FALSE;
    program->number_of_eat = -1;
    program->eat_count = 0;
    program->start_timestamp = get_time();
    if(program->start_timestamp == 0)
        return (error_handler(TIME_ERROR), FALSE);
    program->is_locked = FALSE;
    program->dead_flag = FALSE;
    if(ac == 6) 
	{
        program->is_limited = TRUE;
        program->number_of_eat = ft_atoi(av[5]);
        if(!program->number_of_eat)
            return (error_handler(INPUT_ERROR), FALSE);
    }
	program->philos_arr = malloc(sizeof(t_philo) * program->philo_count);
    if (!program->philos_arr)
        error_handler(MALLOC_ERROR);
	program->semaphore = "/my_semaphore";
    return (TRUE);
}
