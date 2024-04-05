#ifndef PHILO_H
#define PHILO_H

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <limits.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <fcntl.h>


typedef int t_bool;
typedef struct s_philo t_philo;
typedef struct s_program t_program;

struct s_program
{
	char *semaphore;
	sem_t *forks;
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
	t_philo *philos_arr;
	pthread_mutex_t wait_mutex;
};

struct s_philo
{
	t_program *program;
	pid_t philo_id;
	int	philo_index;
	int last_eat;
	pthread_mutex_t last_eat_lock;
};
#define UNINITIALIZED_ID -15
enum e_ERROR_MODES
{
	INPUT_ERROR,
	TIME_ERROR,
	MALLOC_ERROR,
	CREATE_THREAD_ERROR,
	JOIN_THREAD_ERROR,
	MUTEX_INIT_ERROR
};

enum e_BOOLEAN
{
	FALSE,
	TRUE
};

enum e_ITER_MODES
{
	CREATE_THREADS,
	JOIN_THREADS,
	LINK_FORKS,
	DESTROY_FORKS
};

enum e_FORKS
{
	RIGHT_FORK,
	LEFT_FORK
};

enum e_CLEAN_MODES
{
	CLEAN_ALL,
	CLEAN_PROGRAM
};


// GENERAL UTLS
void error_handler(int mode);
int parse_and_check(int ac, char **av, t_program *original);
int	ft_atoi(const char *str);
void clean_all(t_program *program, int mode);
void init_philo(t_program *program);
void *observer_of_all(void *void_program);
int check_dead(t_program *program);
void clean_on_error(t_program *program, t_philo *philos_arr, int current);
void set_as_dead(t_program *program);

// TIME UTILS
time_t get_time(void);
time_t get_timestamp(t_program *program);
int	ft_usleep(size_t milliseconds);

// PRINTING UTILS
int print_thinking(t_philo *philo);
int print_eating(t_philo *philo);
int print_sleeping(t_philo *philo);
int print_took_fork(t_philo *philo, int mode);
void print_error(char *str);


#endif