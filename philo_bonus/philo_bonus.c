#include "philo_bonus.h"

void error_handler(t_program *program, int mode)
{
    (void)program;
	if (mode == INPUT_ERROR)
		print_error("Error: Invalid input!\n");
	else if (mode == TIME_ERROR)
		print_error("Error: Could not retrieve current time!\n");
	else if (mode == MALLOC_ERROR)
		print_error("Error: Could not allocate memory!\n");
    // if(program)
    //     clean_all(program);
	exit(EXIT_FAILURE);
}


void print_program_info(t_program *prog)
 {
    printf("philo_count: %d\n", prog->philo_count);
    printf("time_to_die: %d\n", prog->time_to_die);
    printf("time_to_eat: %d\n", prog->time_to_eat);
    printf("time_to_sleep: %d\n", prog->time_to_sleep);
    printf("is_limited: %d\n", prog->is_limited);
    printf("number_of_eat: %d\n", prog->number_of_eat);
    printf("dead_flag: %d\n", prog->dead_flag);
    printf("is_first_run: %d\n", prog->is_first_run);
}

int main(int ac, char **av)
{
	t_program program;


	parse_and_check(ac, av, &program);
	print_program_info(&program);
}