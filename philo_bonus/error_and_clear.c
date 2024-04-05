#include "philo.h"


void print_error(char *str)
{
	int i;

	i = 0;
	while(str[i])
	{
		write(2, &str[i], 1);
		i++;
	}
}

void error_handler(int mode)
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
	exit(EXIT_FAILURE);
}
