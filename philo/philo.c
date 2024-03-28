#include "philo.h"

void print_program_info(struct s_program *prog) {
    printf("philo_count: %d\n", prog->philo_count);
    printf("time_to_die: %d\n", prog->time_to_die);
    printf("time_to_eat: %d\n", prog->time_to_eat);
    printf("time_to_sleep: %d\n", prog->time_to_sleep);
    printf("is_limited: %d\n", prog->is_limited);
    printf("number_of_eat: %d\n", prog->number_of_eat);
    printf("dead_flag: %d\n", prog->dead_flag);
    printf("is_first_run: %d\n", prog->is_first_run);
    // Print other members if needed
}

int main(int ac, char **av)
{
    t_program original;

    parse_and_check(ac, av, &original);
    // print_program_info(&original);
	pthread_mutex_init(&original.start_lock, NULL);
    init_philo(&original);
    pthread_mutex_destroy(&original.start_lock);
    return 0;
}
