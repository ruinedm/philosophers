#include "philo.h"


void *philo_observer_routine(void *void_philo)
{
    t_philo *philo;
    t_program *program;
    time_t time;

    philo = (t_philo *)void_philo;
    program = philo->program;
    while (TRUE)
    {
        sem_wait(philo->last_eat_sem);
        time = get_timestamp(program);
        if(time - philo->last_eat > program->time_to_die)
        {
            sem_wait(program->print_sem);
            printf("%ld %i has died", get_timestamp(program), philo->philo_index + 1);
            exit(DEAD_PHILO);
        }
        if(program->is_limited)
        {
            if(philo->eat_count >= program->number_of_eat)
            {
                sem_post(program->forks);
                sem_post(program->forks);
                exit(EATEN_ENOUGH);
            }
        }
        sem_post(philo->last_eat_sem);
        usleep(100);
    }
    return (NULL);
}


void philo_routine(t_philo *philo)
{
    char *philo_index;
    t_program *program;

    philo_index = ft_itoa(philo->philo_index);
    program = philo->program;
    philo->last_eat_str = ft_strjoin("/last_eat_", philo_index);
    philo->eaten_enough_str = ft_strjoin("/eaten_enough_", philo_index);
    philo->thread_sync_str = ft_strjoin("/thread_sync_", philo_index);
    sem_unlink(philo->last_eat_str);
    philo->last_eat_sem = sem_open(philo->last_eat_str, O_CREAT | O_EXCL, 0644, 1);
    if(philo->last_eat_sem == SEM_FAILED)
    {
        perror("sem_open");
        exit(EXIT_FAILURE);
    }
    sem_unlink(philo->eaten_enough_str);
    philo->eaten_enough_sem = sem_open(philo->eaten_enough_str, O_CREAT | O_EXCL, 0644, 1);
    if(philo->eaten_enough_sem == SEM_FAILED)
    {
        perror("sem_open");
        exit(EXIT_FAILURE);
    }
    sem_unlink(philo->thread_sync_str);
    philo->thread_sync_sem = sem_open(philo->thread_sync_str, O_CREAT | O_EXCL, 0644, 1);
    if(philo->thread_sync_sem == SEM_FAILED)
    {
        perror("sem_open");
        exit(EXIT_FAILURE);
    }
    pthread_create(&philo->philo_observer, NULL, philo_observer_routine, (void *)philo);
    pthread_detach(philo->philo_observer);
    while (TRUE)
    {
        sem_wait(program->forks);
        sem_wait(program->print_sem);
        printf("%ld %i has taken a fork\n", get_timestamp(program), philo->philo_index + 1);
        sem_post(program->print_sem);
        sem_wait(program->forks);
        sem_wait(program->print_sem);
        printf("%ld %i has taken a fork\n", get_timestamp(program), philo->philo_index + 1);
        sem_post(program->print_sem);
        sem_wait(philo->last_eat_sem);
        philo->last_eat = get_timestamp(program);
        philo->eat_count++;
        sem_post(philo->last_eat_sem);
        sem_wait(program->print_sem);
        printf("%ld %i is eating\n", get_timestamp(program), philo->philo_index + 1);
        sem_post(program->print_sem);
        ft_usleep(program->time_to_eat);
        sem_post(program->forks);
        sem_post(program->forks);
        sem_wait(program->print_sem);
        printf("%ld %d is sleeping\n", get_timestamp(program), philo->philo_index + 1);
        sem_post(program->print_sem);
        ft_usleep(program->time_to_sleep);
        sem_wait(program->print_sem);
        printf("%ld %i is thinking\n", get_timestamp(program), philo->philo_index + 1);
        sem_post(program->print_sem);
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
            if (waitpid(program->philos_arr[i].philo_id, &status, WNOHANG) > 0)
            {
                if (WIFEXITED(status))
                {
                    if(WEXITSTATUS(status) == DEAD_PHILO)
                    {
                        kill_all(program, i);
                        exit(EXIT_SUCCESS);
                    }
                    else if (WEXITSTATUS(status) == EATEN_ENOUGH)
                        program->philos_done_eating++;
                    else if (WEXITSTATUS(status) == EXIT_FAILURE)
                    {
                        kill_all(program, i);
                        exit(EXIT_FAILURE);
                    }
                }
            }
            if(program->is_limited && program->philos_done_eating == program->philo_count)
                exit(EXIT_SUCCESS);
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
    sem_unlink("/print_sem");
    program->print_sem = sem_open("/print_sem", O_CREAT | O_EXCL, 0644, 1);
    if(program->forks == SEM_FAILED)
    {
        perror("sem_open");
        exit(EXIT_FAILURE);
    }
    while(i < program->philo_count)
    {
        program->philos_arr[i].philo_index = i;
        program->philos_arr[i].eat_count = 0;
        program->philos_arr[i].program = program;
        program->philos_arr[i].philo_id = fork();
        program->philos_arr[i].last_eat = 0;
        program->philos_arr[i].already = 0;
        if(!program->philos_arr[i].philo_id)
            philo_routine(&program->philos_arr[i]);
        i++;
    }
    observe_philos(program);
}
