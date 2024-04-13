#include "philo.h"

int create_threads(t_program *program) 
{
    int i = 0;
    int arr_size = program->philo_count;
    t_philo **philos_arr = &(program->philos_arr);

    while (i < arr_size) 
	{
        if(pthread_create(&(*philos_arr)[i].philo_id, NULL, philo_routine, &(*philos_arr)[i]))
			return (set_as_dead(program), error_handler(CREATE_THREAD_ERROR), clean_all(program, CLEAN_ALL), FALSE);
        i++;
    }
    if(pthread_create(&program->observer_id, NULL, observer_of_all, program))
		return (set_as_dead(program), error_handler(CREATE_THREAD_ERROR), clean_all(program, CLEAN_ALL), FALSE);
	return (TRUE);
}

void link_forks(t_program *program)
 {
    int i = 0;
    int arr_size = program->philo_count;
    t_philo **philos_arr = &(program->philos_arr);

    while (i < arr_size) 
	{
        if (i == arr_size - 1 && i != 0)
            (*philos_arr)[i].left_fork = (*philos_arr)[0].right_fork;
        else if (i != arr_size)
            (*philos_arr)[i].left_fork = (*philos_arr)[i + 1].right_fork;
        i++;
    }
}

int join_threads(t_program *program) 
{
    int i = 0;
    int arr_size = program->philo_count;
    t_philo **philos_arr = &(program->philos_arr);

    while (i < arr_size)
	 {
        if(pthread_join((*philos_arr)[i].philo_id, NULL))
			return (set_as_dead(program), error_handler(CREATE_THREAD_ERROR), clean_all(program, CLEAN_ALL), FALSE);
        i++;
    }
    if(pthread_join(program->observer_id, NULL))
		return (set_as_dead(program), error_handler(CREATE_THREAD_ERROR), clean_all(program, CLEAN_ALL), FALSE);
	return (TRUE);
}


int start_the_simulation(t_program *program)
{
	program->start_flag = FALSE;
	link_forks(program);
	if(!create_threads(program))
		return (FALSE);
	pthread_mutex_lock(&program->start_lock);
	program->start_flag = TRUE;
	pthread_mutex_unlock(&program->start_lock);
	if(!join_threads(program))
		return (FALSE);
	return (TRUE);
}

int init_philo(t_program *program)
{
	t_philo *philos_arr;
	int i;

	i = 0;
	philos_arr = malloc(sizeof(t_philo) * program->philo_count);
	if(philos_arr == NULL)
		return (error_handler(MALLOC_ERROR), clean_all(program, CLEAN_PROGRAM),FALSE);
	while (i < program->philo_count)
	{
		philos_arr[i].program = program;
		philos_arr[i].philo_index = i;
		philos_arr[i].right_fork = malloc(sizeof(pthread_mutex_t));
		if(philos_arr[i].right_fork == NULL)
			return (clean_on_error(program,philos_arr, i), error_handler(MALLOC_ERROR),clean_all(program, CLEAN_PROGRAM), FALSE);
		philos_arr[i].left_fork = NULL;
		philos_arr[i].last_eat = get_timestamp(program);
		if(pthread_mutex_init(&philos_arr[i].last_eat_lock, NULL))
			return (clean_on_error(program,philos_arr, i), error_handler(MALLOC_ERROR),clean_all(program, CLEAN_PROGRAM), FALSE);
		if(pthread_mutex_init(philos_arr[i].right_fork, NULL))
			return (clean_on_error(program,philos_arr, i), error_handler(MALLOC_ERROR),clean_all(program, CLEAN_PROGRAM), FALSE);
		i++;
	}
	program->philos_arr = philos_arr;
	return (start_the_simulation(program));
}
