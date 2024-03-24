#ifndef PHILO_H
#define PHILO_H

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <limits.h>

typedef int t_bool;

typedef struct s_philo
{
	pthread_t philo_id;
	int	philo_index;
	t_bool has_already_eaten;
	size_t time_to_die;
	size_t time_to_sleep;
	size_t time_to_eat;
	pthread_mutex_t my_fork;
	struct s_philo *next;
	struct s_philo *prev;
} t_philo;

typedef struct s_program
{
	pthread_mutex_t start_lock;
	int philo_count;
	int original_time_to_die;
	int original_time_to_eat;
	int original_time_to_sleep;
	t_bool is_limited;
	int number_of_eat;
	int dead_flag;
	t_philo *philo_list;
} t_program;


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
	INITIALIZE_MUTEXES
};



// GENERAL UTLS
void error_handler(int mode);
void init_philo(t_program *program);

void parse_and_check(int ac, char **av, t_program *original);

// CONVERSION UTILS
int	ft_atoi(const char *str);



// LINKED LIST UTILS
t_philo	*ft_lstnew_philo(t_program *program, void *(routine)(void *), int index);
void	ft_lstadd_back(t_philo **lst, t_philo *new);
void	ft_lstiter_philo(t_philo *lst, int mode, int philo_count);
#endif