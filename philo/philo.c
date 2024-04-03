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
    else if (mode == CREATE_THREAD_ERROR)
        print_error("Error: Could not create thread!\n");
    else if (mode == JOIN_THREAD_ERROR)
        print_error("Error: Could not join thread!\n");
    else if (mode == MUTEX_INIT_ERROR)
        print_error("Error: Could not initialize mutex!\n");
}

void clean_program(t_program *program)
{
    pthread_mutex_destroy(&program->print_lock);
    pthread_mutex_destroy(&program->dead_lock);
    if(program->is_limited == TRUE)
        pthread_mutex_destroy(&program->count_lock);
}

void clean_philos(t_program *program)
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
}

void clean_all(t_program *program, int mode)
{
    int i;

    i = 0;
    if(mode == CLEAN_ALL)
    {
        clean_philos(program);
        clean_program(program);
    }
    else if (mode == CLEAN_PROGRAM)
        clean_program(program);
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


