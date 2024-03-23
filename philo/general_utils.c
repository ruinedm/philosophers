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
	if(mode == INPUT_ERROR)
		print_error("Invalid input!\n");
	exit(EXIT_FAILURE);
}