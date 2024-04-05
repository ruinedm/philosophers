#include "philo.h"


void philo_routine(t_philo *philo)
{
    t_program *program;

    program = philo->program;
    while (TRUE)
    {
        sem_wait(program->forks);
        printf("%ld %i has taken a fork\n", get_timestamp(program), philo->philo_index + 1);
        sem_wait(program->forks);
        printf("%ld %i has taken a fork\n", get_timestamp(program), philo->philo_index + 1);
        printf("%ld %i is eating\n", get_timestamp(program), philo->philo_index + 1);
        ft_usleep(program->time_to_eat);
        sem_post(program->forks);
        sem_post(program->forks);
        printf("%ld %d is sleeping\n", get_timestamp(program), philo->philo_index + 1);
        ft_usleep(program->time_to_sleep);
        printf("%ld %i is thinking\n", get_timestamp(program), philo->philo_index + 1);
    }
    exit(EXIT_SUCCESS);
}


void init_philo(t_program *program)
{
    pid_t pid;
    int i;

    i = 0;
    sem_unlink(program->semaphore);
    program->forks = sem_open(program->semaphore, O_CREAT | O_EXCL, 0644, program->philo_count);
    if(program->forks == SEM_FAILED)
    {
        perror("sem_open");
        exit(EXIT_FAILURE);
    }
    while(i < program->philo_count)
    {
        program->philos_arr[i].philo_index = i;
        program->philos_arr[i].philo_id = fork();
        program->philos_arr[i].program = program;
        if(!program->philos_arr[i].philo_id)
            philo_routine(&program->philos_arr[i]);
        i++;
    }
    while (wait(NULL) != -1);
}
