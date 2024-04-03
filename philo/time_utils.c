#include "philo.h"

time_t get_time(void)
{
    struct timeval time;

    if(gettimeofday(&time, NULL) != 0)
        return (0);
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
	if(start == 0)
		return (-1);
	while ((get_time() - start) < milliseconds)
		usleep(500);
	return (0);
}