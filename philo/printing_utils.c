#include "philo.h"

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

void print_thinking(t_philo *philo)
{
	t_program *program;

	program = philo->program;
	pthread_mutex_lock(&program->print_lock);
	printf("%ld %d is thinking\n", get_timestamp(program), philo->philo_index + 1);
	pthread_mutex_unlock(&program->print_lock);
}

void print_sleeping(t_philo *philo)
{
	t_program *program;

	program = philo->program;
	pthread_mutex_lock(&program->print_lock);
	printf("%ld %d is sleeping\n", get_timestamp(program), philo->philo_index + 1);
	pthread_mutex_unlock(&program->print_lock);
	ft_usleep(program->time_to_sleep);
}

void print_took_fork(t_philo *philo)
{
	t_program *program;

	program = philo->program;
	pthread_mutex_lock(&program->print_lock);
	printf("%ld %d has taken a fork\n", get_timestamp(program), philo->philo_index + 1);
	pthread_mutex_unlock(&program->print_lock);
}

void print_eating(t_philo *philo)
{
	t_program *program;

	program = philo->program;
	pthread_mutex_lock(&program->print_lock);
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
}

