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

t_philo *init_philo(t_program *program)
{
	int philo_count;
	t_philo *philo_head;

	philo_count = 0;
	philo_head = ft_lstnew_philo();
	pthread_create(&philo_head->philo_id, NULL, philo_routine, (void *)program);

	pthread_join(philo_head->philo_id, NULL);
}