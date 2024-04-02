#include "philo.h"


// int check_dead(t_philo *philo)
// {
// 	t_program *program;

// 	program = philo->program;
// 	pthread_mutex_lock(&program->dead_lock);
// 	if(program->dead_flag)
// 	{
// 		pthread_mutex_unlock(&program->dead_lock);
// 		return (TRUE);
// 	}
// 	pthread_mutex_unlock(&program->dead_lock);
// 	return (FALSE);
// }

void print_error(char *str)
{
	int i;

	i = 0;
	while(str[i])
	{
		write(2, &str[i], 1);
		i++;
	}
}

int print_thinking(t_philo *philo)
{
	t_program *program;

	program = philo->program;
	pthread_mutex_lock(&program->print_lock);
	if(check_dead(program))
	{
		pthread_mutex_unlock(&program->print_lock);
		return FALSE;
	}
	printf("%ld %d is thinking\n", get_timestamp(program), philo->philo_index + 1);
	pthread_mutex_unlock(&program->print_lock);
	return TRUE;
}

int print_sleeping(t_philo *philo)
{
	t_program *program;

	program = philo->program;

	pthread_mutex_lock(&program->print_lock);
	if(check_dead(program))
	{
		pthread_mutex_unlock(&program->print_lock);
		return FALSE;
	}
	printf("%ld %d is sleeping\n", get_timestamp(program), philo->philo_index + 1);
	pthread_mutex_unlock(&program->print_lock);
	ft_usleep(program->time_to_sleep);
	return TRUE;
}

int print_took_fork(t_philo *philo, int mode)
{
	t_program *program;

	program = philo->program;
	pthread_mutex_lock(&program->print_lock);
	if(check_dead(program))
	{
		pthread_mutex_unlock(&program->print_lock);
		if(mode == RIGHT_FORK)
			pthread_mutex_unlock(philo->right_fork);
		else
		{
			pthread_mutex_unlock(philo->right_fork);
			pthread_mutex_unlock(philo->left_fork);
		}
		return FALSE;
	}
	printf("%ld %d has taken a fork\n", get_timestamp(program), philo->philo_index + 1);
	pthread_mutex_unlock(&program->print_lock);
	return TRUE;
}

int print_eating(t_philo *philo)
{
	t_program *program;

	program = philo->program;
	pthread_mutex_lock(&program->print_lock);
	if(check_dead(program))
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(&program->print_lock);
		return FALSE;
	}
	printf("%ld %d is eating\n", get_timestamp(program), philo->philo_index + 1);
	pthread_mutex_unlock(&program->print_lock);
	pthread_mutex_lock(&philo->last_eat_lock);
	philo->last_eat = get_timestamp(program);
	pthread_mutex_unlock(&philo->last_eat_lock);
	ft_usleep(program->time_to_eat);
	if(program->is_limited == TRUE)
	{
		pthread_mutex_lock(&program->count_lock);
		philo->program->eat_count++;
		pthread_mutex_unlock(&program->count_lock);
	}
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	return TRUE;
}

