#include "philo.h"

time_t get_time(void)
{
    struct timeval time;

    if(gettimeofday(&time, NULL) != 0)
        error_handler(TIME_ERROR);
    return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

time_t get_timestamp(t_program *program)
{
	return (get_time() - program->start_timestamp);
}

int	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = get_time();
	while ((get_time() - start) < milliseconds)
		usleep(500);
	return (0);
}