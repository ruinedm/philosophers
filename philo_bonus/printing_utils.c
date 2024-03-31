#include "philo_bonus.h"

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

	printf("%ld %d is thinking\n", get_timestamp(program), philo->philo_index + 1);

}

void print_sleeping(t_philo *philo)
{
	t_program *program;

	program = philo->program;

	printf("%ld %d is sleeping\n", get_timestamp(program), philo->philo_index + 1);

	ft_usleep(program->time_to_sleep);
}

void print_took_fork(t_philo *philo)
{
	t_program *program;

	program = philo->program;

	printf("%ld %d has taken a fork\n", get_timestamp(program), philo->philo_index + 1);

}

void print_eating(t_philo *philo)
{
	t_program *program;

	program = philo->program;
	philo->last_eat = get_timestamp(program);

	philo->last_eat = get_timestamp(program);
	printf("%ld %d is eating\n", get_timestamp(program), philo->philo_index + 1);

	ft_usleep(program->time_to_eat);
	if(program->is_limited == TRUE)
	{
		philo->program->eat_count++;
	}
}

