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
	pthread_mutex_t print_lock;
	pthread_mutex_t count_lock;
	int is_locked;
	int philo_count;
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;
	time_t start_timestamp;
	t_bool is_limited;
	int number_of_eat;
	int eat_count;
	int dead_flag;
	t_bool is_first_run;
	t_philo *philos_arr;
};

struct s_philo
{
	t_program *program;
	pthread_t philo_id;
	int	philo_index;
	int last_eat;
	pthread_mutex_t last_eat_lock;
	pthread_mutex_t *right_fork;
	pthread_mutex_t *left_fork;
};


#define TIME_NOT_INITALIZED -1

enum e_ERROR_MODES
{
	INPUT_ERROR,
	TIME_ERROR,
	MALLOC_ERROR,
};

enum e_BOOLEAN
{
	FALSE,
	TRUE
};

enum e_ITER_MODES
{
	CREATE_THREADS,
	DETACH_THREADS,
	LINK_FORKS,
	DESTROY_FORKS
};


// GENERAL UTLS
void error_handler(t_program *program, int mode);
void parse_and_check(int ac, char **av, t_program *original);
int	ft_atoi(const char *str);
void clean_all(t_program *program);
void set_iter(t_philo **philos_arr, int arr_size, int mode);
void init_philo(t_program *program);


// TIME UTILS
time_t get_time(void);
time_t get_timestamp(t_program *program);
int	ft_usleep(size_t milliseconds);

// PRINTING UTILS
void print_thinking(t_philo *philo);
void print_eating(t_philo *philo);
void print_sleeping(t_philo *philo);
void print_took_fork(t_philo *philo);
void print_error(char *str);


#endif