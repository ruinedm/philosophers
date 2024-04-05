#include "philo.h"


int main(int ac, char **av)
{ 
    t_program program;

    if(!parse_and_check(ac, av, &program))
        return 1;
    init_philo(&program);
    sem_close(program.forks);
    return 0;
}


