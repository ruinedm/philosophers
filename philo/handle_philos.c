#include "philo.h"



static void *philo_routine(void *void_philo)
{
	t_philo *philo;
	t_program *program;

	philo = (t_philo *)void_philo;
	program = philo->program;
	while(1)
	{
		printf("%li %i is thinking\n", get_time() - program->start_timestamp, philo->philo_index + 1);
		ft_usleep(program->time_to_sleep);
		printf("%li %i is sleeping\n", get_time() - program->start_timestamp, philo->philo_index + 1);
	}
	return (NULL);
}


void init_philo(t_program *program)
{
	t_philo philos_arr[program->philo_count];
	int i;

	i = 0;
	while (i < program->philo_count)
	{
		philos_arr[i].program = program;
		philos_arr[i].has_already_eaten = -1;
		philos_arr[i].philo_index = i;
		pthread_create(&philos_arr[i].philo_id, NULL, philo_routine, &philos_arr[i]);
		// printf("Created philo: %i\n", i);
		i++;
	}
	program->is_locked = FALSE;
	program->philos_arr = philos_arr;
	i = 0;
	while (i < program->philo_count)
	{
		pthread_join(philos_arr[i].philo_id, NULL);
		i++;
	}
}
