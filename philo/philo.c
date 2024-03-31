#include "philo.h"

void print_program_info(t_program *prog)
 {
    printf("philo_count: %d\n", prog->philo_count);
    printf("time_to_die: %d\n", prog->time_to_die);
    printf("time_to_eat: %d\n", prog->time_to_eat);
    printf("time_to_sleep: %d\n", prog->time_to_sleep);
    printf("is_limited: %d\n", prog->is_limited);
    printf("number_of_eat: %d\n", prog->number_of_eat);
    printf("dead_flag: %d\n", prog->dead_flag);
    printf("is_first_run: %d\n", prog->is_first_run);
}


void observer_of_all(t_program *program)
{
    int i;
    int count;

    count = 0;
    while (TRUE)
    {
        i = 0;
        while (i < program->philo_count)
        {
            if (get_timestamp(program) - program->philos_arr[i].last_eat > program->time_to_die)
            {
                pthread_mutex_lock(&program->print_lock);
                printf("%ld %d died\n", get_timestamp(program), i + 1);
                pthread_mutex_unlock(&program->print_lock);
                program->dead_flag = TRUE;
                return ;
            }
            i++;
        }
    }
}

int main(int ac, char **av)
{
    t_program original;

    parse_and_check(ac, av, &original);
    // print_program_info(&original);
    init_philo(&original);
    observer_of_all(&original);
    set_iter(&original.philos_arr, original.philo_count, DESTROY_FORKS);
    return 0;
}


