#include "philo.h"


void first_eat(t_philo *philo)
{
	t_program *program;

	program = philo->program;
	if(philo->philo_index % 2 == 0)
	{
		pthread_mutex_lock(philo->right_fork);
		printf("%i has taken the right fork\n", philo->philo_index);
		pthread_mutex_lock(philo->left_fork);
		printf("%i has taken the left fork\n", philo->philo_index);
		printf("%i is eating\n", philo->philo_index);
		usleep(program->original_time_to_eat);
		pthread_mutex_unlock(philo->right_fork);
		printf("%i has put down the right fork\n", philo->philo_index);
		pthread_mutex_unlock(philo->left_fork);
		printf("%i has put down the left fork\n", philo->philo_index);
	}
	program->is_first_run = FALSE;
}

// void eat(t_philo *philo)
// {
// 	if (philo->has_already_eaten == FALSE)
// }

void *philo_routine(void *void_philo)
{
	t_philo *philo;

	philo = (t_philo *)void_philo;
	pthread_mutex_lock(&philo->program->start_lock);
	pthread_mutex_unlock(&philo->program->start_lock);
	while(1)
	{
		printf("%i is thinking\n", philo->philo_index);
		printf("%i is sleeping\n", philo->philo_index);
		usleep(philo->program->original_time_to_sleep);
		if(philo->program->is_first_run)
			first_eat(philo);
		// sleep(1);
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
	ft_lstiter_philo(philo_head, SETUP_LEFT_FORK, program->philo_count);
	pthread_mutex_unlock(&program->start_lock); // CALL FROM MAIN THREAD TO LET THE PHILOS GO
	ft_lstiter_philo(philo_head, JOIN_THREADS, program->philo_count);
	program->philo_list = philo_head;
}
