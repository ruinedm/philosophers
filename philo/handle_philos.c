#include "philo.h"

static void *philo_routine(void *void_philo)
{
	t_philo *philo;
	t_program *program;

	philo = (t_philo *)void_philo;
	program = philo->program;
	if(philo->philo_index % 2 == 0)
		ft_usleep(program->time_to_eat / 2);
	while(TRUE)
	{
		pthread_mutex_lock(philo->right_fork);
		print_took_fork(philo);
		pthread_mutex_lock(philo->left_fork);
		print_took_fork(philo);
		print_eating(philo);
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		print_sleeping(philo);
		print_thinking(philo);
	}
	return (NULL);
}

void set_iter(t_philo **philos_arr, int arr_size, int mode)
{
	int i;

	i = 0;
	if(mode == CREATE_THREADS)
	{
		while(i < arr_size)
		{
			pthread_create(&(*philos_arr)[i].philo_id, NULL, philo_routine, &(*philos_arr)[i]);
			pthread_detach((*philos_arr)[i].philo_id);
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
}

static void free_forks_on_error(t_program *program, t_philo *philos_arr, int current)
{
	int i;

	i = 0;
	while(i < current)
	{
		pthread_mutex_destroy(philos_arr[i].right_fork);
		free(philos_arr[i].right_fork);
		i++;
	}
	free(philos_arr);
	pthread_mutex_destroy(&program->print_lock);
}

void init_philo(t_program *program)
{
	t_philo *philos_arr;
	int i;

	i = 0;
	philos_arr = malloc(sizeof(t_philo) * program->philo_count);
	if(philos_arr == NULL)
		error_handler(program, MALLOC_ERROR);
	while (i < program->philo_count)
	{
		philos_arr[i].program = program;
		philos_arr[i].philo_index = i;
		philos_arr[i].right_fork = malloc(sizeof(pthread_mutex_t));
		if(philos_arr[i].right_fork == NULL)
			return (free_forks_on_error(program,philos_arr, i), error_handler(program, MALLOC_ERROR));
		philos_arr[i].left_fork = NULL;
		philos_arr[i].last_eat = 0;
		pthread_mutex_init(&philos_arr[i].last_eat_lock, NULL);
		pthread_mutex_init(philos_arr[i].right_fork, NULL);
		i++;
	}
	program->philos_arr = philos_arr;
	set_iter(&program->philos_arr, program->philo_count, LINK_FORKS);
	set_iter(&program->philos_arr, program->philo_count, CREATE_THREADS);
}
