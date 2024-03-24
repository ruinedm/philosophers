#include "philo.h"

void *philo_routine(void *void_philo)
{
	t_philo *philo;

	philo = (t_philo *)void_philo;
	while(1)
	{
		pthread_mutex_lock(philo->ptr_start_lock);
		printf("%i is thinking\n", philo->philo_index);
		pthread_mutex_unlock(philo->ptr_start_lock);
		sleep(2);
	}
}

void init_philo(t_program *program)
{
	int i;
	t_philo *philo_head;
	t_philo *current_philo;

	i = 0;
	philo_head = NULL;
	pthread_mutex_lock(&program->start_lock);
	while(i < program->philo_count)
	{
		current_philo = ft_lstnew_philo(program, philo_routine, i);
		ft_lstadd_back(&philo_head, current_philo);
		i++;
	}
	pthread_mutex_unlock(&program->start_lock); // CALL FROM MAIN THREAD TO LET THE PHILOS GO
	ft_lstiter_philo(philo_head, JOIN_THREADS, program->philo_count);
	ft_lstiter_philo(philo_head, SETUP_LEFT_FORK, program->philo_count);
	program->philo_list = philo_head;
}