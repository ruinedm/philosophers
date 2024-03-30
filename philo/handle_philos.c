#include "philo.h"



static void *philo_routine(void *void_philo)
{
	t_philo *philo;
	t_program *program;

	philo = (t_philo *)void_philo;
	program = philo->program;
	while(1)
	{
		printf("%li %i is thinking\n", get_timestamp(program), philo->philo_index + 1);
		ft_usleep(program->time_to_sleep);
		printf("%li %i is sleeping\n", get_timestamp(program), philo->philo_index + 1);
	}
	return (NULL);
}

static void set_iter(t_philo **philos_arr, int arr_size, int mode)
{
	int i;

	i = 0;
	if(mode == CREATE_THREADS)
	{
		while(i < arr_size)
		{
			pthread_create(&(*philos_arr)[i].philo_id, NULL, philo_routine, &(*philos_arr)[i]);
			i++;
		}
	}
	else if(mode == LINK_FORKS)
	{
		while(i < arr_size)
		{
			if(i == arr_size - 1)
				(*philos_arr)[i].left_fork = (*philos_arr)[0].right_fork;
			else
				(*philos_arr)[i].left_fork = (*philos_arr)[i + 1].right_fork;
			i++;
		}
	}
	else if(mode == JOIN_THREADS)
	{
		while(i < arr_size)
		{
			pthread_join((*philos_arr)[i].philo_id, NULL);
			i++;
		}
	}
	else if(mode == DESTROY_FORKS)
	{
		while(i < arr_size)
		{
			pthread_mutex_destroy((*philos_arr)[i].right_fork);
			i++;
		}
	}
}

void init_philo(t_program *program)
{
	t_philo philos_arr[program->philo_count];
	int i;

	i = 0;
	pthread_mutex_init(&program->print_lock, NULL);
	while (i < program->philo_count)
	{
		philos_arr[i].program = program;
		philos_arr[i].has_already_eaten = -1;
		philos_arr[i].philo_index = i;
		philos_arr[i].right_fork = malloc(sizeof(pthread_mutex_t));
		philos_arr[i].left_fork = NULL;
		pthread_mutex_init(philos_arr[i].right_fork, NULL);
		i++;
	}
	program->is_locked = FALSE;
	program->philos_arr = philos_arr;
	set_iter(&program->philos_arr, program->philo_count, LINK_FORKS);
	set_iter(&program->philos_arr, program->philo_count, CREATE_THREADS);
	set_iter(&program->philos_arr, program->philo_count, JOIN_THREADS);
	set_iter(&program->philos_arr, program->philo_count, DESTROY_FORKS);
	pthread_mutex_destroy(&program->print_lock);
}
