#include "philo.h"

void *philo_routine(void *void_program)
{
	t_program *program;

	program = (t_program *)void_program;
	pthread_mutex_lock(&program->start_lock);
	printf("Yo i am a philosopher and the count is %i\n", program->philo_count);
	pthread_mutex_unlock(&program->start_lock);
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
		printf("Created philo %i\n", i);
		ft_lstadd_back(&philo_head, current_philo);
		i++;
	}
	pthread_mutex_unlock(&program->start_lock); // CALL FROM MAIN THREAD TO LET THE PHILOS GO
	ft_lstiter_philo(philo_head, JOIN_THREADS, program->philo_count);
	program->philo_list = philo_head;
}