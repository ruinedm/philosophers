#include "philo.h"


void *philo_observer_routine(void *void_philo)
{
    t_philo *philo;
    t_program *program;

    philo = (t_philo *)void_philo;
    program = philo->program;
    ft_usleep(2);
    while (TRUE)
    {
        sem_wait(philo->last_eat_sem);
        if(get_timestamp(program) - philo->last_eat > program->time_to_die)
            exit(DEAD_PHILO);
        sem_post(philo->last_eat_sem);
        
    }
    return (NULL);
}

void philo_routine(t_philo *philo)
{
    char *last_eat_str_sem;
    t_program *program;

    program = philo->program;
    last_eat_str_sem = ft_strjoin("/last_eat_", ft_itoa(philo->philo_index));
    sem_unlink(last_eat_str_sem);
    philo->last_eat_sem = sem_open(last_eat_str_sem, O_CREAT | O_EXCL, 0644, 1);
    if(philo->last_eat_sem == SEM_FAILED)
    {
        perror("sem_open");
        exit(EXIT_FAILURE);
    }
    pthread_create(&philo->philo_observer, NULL, philo_observer_routine, (void *)philo);
    pthread_detach(philo->philo_observer);
    if(philo->philo_index > philo->program->philo_count / 2)
        ft_usleep(200);
    while (TRUE)
    {
        sem_wait(program->forks);
        printf("%ld %i has taken a fork\n", get_timestamp(program), philo->philo_index + 1);
        sem_wait(program->forks);
        printf("%ld %i has taken a fork\n", get_timestamp(program), philo->philo_index + 1);
        printf("%ld %i is eating\n", get_timestamp(program), philo->philo_index + 1);
        sem_wait(philo->last_eat_sem);
        philo->last_eat = get_timestamp(program);
        sem_post(philo->last_eat_sem);
        ft_usleep(program->time_to_eat);
        sem_post(program->forks);
        sem_post(program->forks);
        printf("%ld %d is sleeping\n", get_timestamp(program), philo->philo_index + 1);
        ft_usleep(program->time_to_sleep);
        printf("%ld %i is thinking\n", get_timestamp(program), philo->philo_index + 1);
    }
    exit(EXIT_SUCCESS);
}

void kill_all(t_program *program, int already_dead)
{
    int i;

    i = 0;
    while(i < program->philo_count)
    {
        if(i != already_dead)
            kill(program->philos_arr[i].philo_id, SIGKILL);
        i++;
    }
}

void observe_philos(t_program *program)
{
    int i;
    int status;

    while (TRUE)
    {
        i = 0;
        while (i < program->philo_count)
        {
            if (waitpid(program->philos_arr[i].philo_id, &status, WNOHANG) != -1)
            {
                if (WIFEXITED(status) && WEXITSTATUS(status) == DEAD_PHILO)
                {
                    printf("%ld %i has died\n", get_timestamp(program), i + 1);
                    kill_all(program, i);
                    exit(EXIT_SUCCESS);
                }
            }
            i++;
        }
    }
}
void init_philo(t_program *program)
{
    pid_t pid;
    int i;

    i = 0;
    program->philos_arr = malloc(sizeof(t_philo) * program->philo_count);
    if (!program->philos_arr)
        error_handler(MALLOC_ERROR);
    sem_unlink("/fork_semaphore");
    program->forks = sem_open("/fork_semaphore", O_CREAT | O_EXCL, 0644, program->philo_count);
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
        program->philos_arr[i].last_eat = get_timestamp(program);
        if(!program->philos_arr[i].philo_id)
            philo_routine(&program->philos_arr[i]);
        i++;
    }
    observe_philos(program);
}
