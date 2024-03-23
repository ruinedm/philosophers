#include "philo.h"

void *philo_routine(void *void_program)
{
	t_program *program;

	program = (t_program *)void_program;
	printf("I am a waiting philosopher :D\n");
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
	while(i < program->philo_count)
	{
		current_philo = ft_lstnew_philo(program, philo_routine, i);
		ft_lstadd_back(&philo_head, current_philo);
		i++;
	}
	ft_lstiter_join(philo_head);
	program->philo_list = philo_head;
}