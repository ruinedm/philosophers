#ifndef PHILO_H
#define PHILO_H

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <limits.h>
#include <sys/time.h>
typedef int t_bool;

typedef struct s_philo t_philo;
typedef struct s_program t_program;


struct s_program
{
	pthread_mutex_t start_lock;
	int philo_count;
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;
	t_bool is_limited;
	int number_of_eat;
	int dead_flag;
	t_bool is_first_run;
	t_philo *philos_arr;
};

struct s_philo
{
	t_program *program;
	pthread_t philo_id;
	int	philo_index;
	t_bool has_already_eaten;
	pthread_mutex_t *right_fork;
	pthread_mutex_t *left_fork;
};

enum e_ERROR_MODES
{
	INPUT_ERROR,
	MALLOC_ERROR
};

enum e_BOOLEAN
{
	FALSE,
	TRUE
};

enum e_ITER_MODES
{
	JOIN_THREADS,
	LOCK_FORKS,
	SETUP_LEFT_FORK
};



// GENERAL UTLS
void error_handler(int mode);
void parse_and_check(int ac, char **av, t_program *original);
int	ft_atoi(const char *str);


void init_philo(t_program *program);
#endif