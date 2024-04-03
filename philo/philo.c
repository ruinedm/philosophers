#include "philo.h"

void *philo_routine(void *void_philo)
{
	t_philo *philo;
	t_program *program;

	philo = (t_philo *)void_philo;
	program = philo->program;
    pthread_mutex_lock(&program->start_lock);
    pthread_mutex_unlock(&program->start_lock);
	if(philo->philo_index % 2 == 0)
		ft_usleep(program->time_to_eat / 2);
	while(TRUE)
	{
		pthread_mutex_lock(philo->right_fork);
		if(!print_took_fork(philo, RIGHT_FORK))
			break;
		pthread_mutex_lock(philo->left_fork);
		if(!print_took_fork(philo, LEFT_FORK))
			break;
		if(!print_eating(philo))
			break;
		if(!print_sleeping(philo))
			break;
		if(!print_thinking(philo))
			break;
	}
	return (NULL);
}


int main(int ac, char **av)
{ 
    t_program program;

    if(!parse_and_check(ac, av, &program))
        return 1;
    if(!init_philo(&program))
        return 1;
    clean_all(&program, CLEAN_ALL);
    return 0;
}


