#include "philo.h"


static void *philo_routine(void *void_philo)
{
	t_philo *philo;

	philo = (t_philo *)void_philo;
	pthread_mutex_lock(&philo->program->start_lock);
	pthread_mutex_unlock(&philo->program->start_lock);
	printf("HELLO FROM PHILO: %i\n", philo->philo_index);
	return (NULL);
}


void init_philo(t_program *program)
{
	t_philo philos_arr[program->philo_count];
	int i;

	i = 0;
	pthread_mutex_lock(&program->start_lock);
	while (i < program->philo_count)
	{
		philos_arr[i].program = program;
		philos_arr[i].has_already_eaten = -1;
		philos_arr[i].philo_index = i;
		pthread_create(&philos_arr[i].philo_id, NULL, philo_routine, &philos_arr[i]);
		printf("Created philo: %i\n", i);
		i++;
	}
	program->philos_arr = philos_arr;
	i = 0;
	pthread_mutex_unlock(&program->start_lock);
	while (i < program->philo_count)
	{
		pthread_join(philos_arr[i].philo_id, NULL);
		i++;
	}
}