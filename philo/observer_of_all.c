#include "philo.h"


void *observer_of_all(void *void_program)
{
	t_program *program;
    int i;

	program = (t_program *)void_program;
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
				pthread_mutex_lock(&program->dead_lock);
				program->dead_flag = TRUE;
				pthread_mutex_unlock(&program->dead_lock);
                pthread_mutex_unlock(&program->print_lock);
                return NULL;
            }
            pthread_mutex_unlock(&program->philos_arr[i].last_eat_lock);
            if(program->is_limited == TRUE)
            {
                pthread_mutex_lock(&program->count_lock);
                if(program->eat_count >= program->philo_count * program->number_of_eat)
                {
                    pthread_mutex_lock(&program->print_lock);
					pthread_mutex_lock(&program->dead_lock);
					program->dead_flag = TRUE;
					pthread_mutex_unlock(&program->dead_lock);
					pthread_mutex_unlock(&program->print_lock);
                    return NULL;
                }
                pthread_mutex_unlock(&program->count_lock);
            }
            i++;
        }
    }
	return NULL;
}