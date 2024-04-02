#include "philo.h"

// void print_program_info(t_program *prog)
//  {
//     printf("philo_count: %d\n", prog->philo_count);
//     printf("time_to_die: %d\n", prog->time_to_die);
//     printf("time_to_eat: %d\n", prog->time_to_eat);
//     printf("time_to_sleep: %d\n", prog->time_to_sleep);
//     printf("is_limited: %d\n", prog->is_limited);
//     printf("number_of_eat: %d\n", prog->number_of_eat);
//     printf("dead_flag: %d\n", prog->dead_flag);
//     printf("is_first_run: %d\n", prog->is_first_run);
// }

void error_handler(t_program *program, int mode)
{
	if (mode == INPUT_ERROR)
		print_error("Error: Invalid input!\n");
	else if (mode == TIME_ERROR)
		print_error("Error: Could not retrieve current time!\n");
	else if (mode == MALLOC_ERROR)
		print_error("Error: Could not allocate memory!\n");
    if(program)
        clean_all(program);
	exit(EXIT_FAILURE);
}

void observer_of_all(t_program *program)
{
    int i;

    while (TRUE)
    {
        i = 0;
        while (i < program->philo_count)
        {
            pthread_mutex_lock(&program->philos_arr[i].last_eat_lock);
            if (get_timestamp(program) - program->philos_arr[i].last_eat > program->time_to_die)
            {
                pthread_mutex_unlock(&program->philos_arr[i].last_eat_lock);
                pthread_mutex_lock(&program->print_lock);
                printf("%ld %d died\n", get_timestamp(program), i + 1);
                //pthread_mutex_unlock(&program->print_lock);
                return ;
            }
            pthread_mutex_unlock(&program->philos_arr[i].last_eat_lock);
            if(program->is_limited == TRUE)
            {
                pthread_mutex_lock(&program->count_lock);
                if(program->eat_count >= program->philo_count * program->number_of_eat)
                {
                    pthread_mutex_lock(&program->print_lock);
                    return ;
                }
                pthread_mutex_unlock(&program->count_lock);
            }
            i++;
        }
    }
}

void clean_all(t_program *program)
{
    int i;

    i = 0;
    while (i < program->philo_count)
    {
        pthread_mutex_destroy(&program->philos_arr[i].last_eat_lock);
        pthread_mutex_destroy(program->philos_arr[i].right_fork);
        free(program->philos_arr[i].right_fork);
        i++;
    }
    free(program->philos_arr);
    pthread_mutex_destroy(&program->print_lock);
    if(program->is_limited == TRUE)
        pthread_mutex_destroy(&program->count_lock);
}

int main(int ac, char **av)
{
    t_program program;

    parse_and_check(ac, av, &program);
    init_philo(&program);
    observer_of_all(&program);
    clean_all(&program);
    return 0;
}


