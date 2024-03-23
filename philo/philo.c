#include "philo.h"


int main(int ac, char **av)
{
    t_program original;

    parse_and_check(ac, av, &original);
	pthread_mutex_init(&original.start_lock, NULL);
    pthread_mutex_lock(&original.start_lock);
    init_philo(&original);
    pthread_mutex_unlock(&original.start_lock);
    pthread_mutex_destroy(&original.start_lock);
    return 0;
}
