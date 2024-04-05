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
#include <signal.h>

typedef int t_bool;
typedef struct s_philo t_philo;
typedef struct s_program t_program;

struct s_program
{
	char *semaphore;
	sem_t *forks;
	sem_t *print_sem;
	sem_t *start_sem;
	int is_locked;
	int philo_count;
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;
	time_t start_timestamp;
	t_bool is_limited;
	int number_of_eat;
	int philos_done_eating;
	int dead_flag;
	t_philo *philos_arr;
};

struct s_philo
{
	pthread_t philo_observer;
	t_program *program;
	pid_t philo_id;
	int	philo_index;
	int last_eat;
	int eat_count;
	sem_t *last_eat_sem;
	sem_t *eaten_enough_sem;
};

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


enum EXIT_STATUS
{
	DEAD_PHILO=2,
	EATEN_ENOUGH
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
char	*ft_strjoin(const char *s1, const char *s2);
char	*ft_itoa(int n);
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