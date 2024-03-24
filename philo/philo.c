#include "philo.h"


int main(int ac, char **av)
{
    t_program original;

    parse_and_check(ac, av, &original);
	pthread_mutex_init(&original.start_lock, NULL);
    init_philo(&original);
    pthread_mutex_destroy(&original.start_lock);
    return 0;
}
