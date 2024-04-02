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

void parse_and_check(int ac, char **av, t_program *program)
{
	if((ac != 5 && ac != 6) || !is_valid_av(ac, av))
		error_handler(NULL, INPUT_ERROR);
	program->philo_count = ft_atoi(av[1]);
	program->time_to_die = ft_atoi(av[2]);
	program->time_to_eat = ft_atoi(av[3]);
	program->time_to_sleep = ft_atoi(av[4]);
	program->is_limited = FALSE;
	program->is_first_run = TRUE;
	program->number_of_eat = -1;
	program->eat_count = 0;
	program->start_timestamp = get_time();
	if(program->start_timestamp == 0)
		error_handler(NULL, TIME_ERROR);
	program->is_locked = FALSE;
	program->dead_flag = FALSE;
	if(ac == 6)
	{
		program->is_limited = TRUE;
		program->number_of_eat = ft_atoi(av[5]);
    	pthread_mutex_init(&program->count_lock, NULL);
	}
	pthread_mutex_init(&program->print_lock, NULL);
	pthread_mutex_init(&program->dead_lock, NULL);
	//printf("PRINT LOCK: %p // COUNT LOCK %p // DEAD LOCK %p\n", &program->print_lock, &program->count_lock, &program->dead_lock);
}
// 0x7ffc0a363f20