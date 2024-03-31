#include "philo.h"


static void *philo_routine(void *void_philo)
{
	t_philo *philo;
	t_program *program;

	philo = (t_philo *)void_philo;
	program = philo->program;
	if(philo->philo_index % 2 == 0)
		ft_usleep(100);
	while(TRUE)
	{
		pthread_mutex_lock(&philo->right_fork->fork);
		print_took_fork(philo);
		pthread_mutex_lock(&philo->left_fork->fork);
		print_took_fork(philo);
		print_eating(philo);
		pthread_mutex_unlock(&philo->right_fork->fork);
		pthread_mutex_unlock(&philo->left_fork->fork);
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
	else if(mode == DETACH_THREADS)
	{
		while(i < arr_size)
		{
			pthread_detach((*philos_arr)[i].philo_id);
			// pthread_DETACH((*philos_arr)[i].philo_id, NULL);
			i++;
		}
	}
	else if(mode == DESTROY_FORKS)
	{
		while(i < arr_size)
		{
			free((*philos_arr)[i].right_fork);
			pthread_mutex_destroy(&(*philos_arr)[i].right_fork->fork);
			i++;
		}
	}
}

void init_philo(t_program *program)
{
	t_philo *philos_arr;
	int i;

	i = 0;
	philos_arr = malloc(sizeof(t_philo) * program->philo_count);
	while (i < program->philo_count)
	{
		philos_arr[i].program = program;
		philos_arr[i].philo_index = i;
		philos_arr[i].right_fork = malloc(sizeof(t_fork));
		philos_arr[i].left_fork = NULL;
		philos_arr[i].eat_count = program->number_of_eat;
		philos_arr[i].last_eat = get_timestamp(program);
		pthread_mutex_init(&philos_arr[i].right_fork->fork, NULL);
		i++;
	}
	program->is_locked = FALSE;
	program->philos_arr = philos_arr;
	set_iter(&program->philos_arr, program->philo_count, LINK_FORKS);
	set_iter(&program->philos_arr, program->philo_count, CREATE_THREADS);
	set_iter(&program->philos_arr, program->philo_count, DETACH_THREADS);
}
