/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboukour <mboukour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 20:53:44 by mboukour          #+#    #+#             */
/*   Updated: 2024/07/25 05:11:04 by mboukour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <limits.h>
# include <sys/time.h>

typedef struct s_philo		t_philo;
typedef struct s_program	t_program;

struct s_program
{
	pthread_mutex_t	print_lock;
	pthread_mutex_t	count_lock;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	start_lock;
	pthread_t		observer_id;
	int				start_flag;
	int				philo_count;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	time_t			start_timestamp;
	int				is_limited;
	int				number_of_eat;
	int				eat_count;
	int				dead_flag;
	int				philos_done_eating;
	t_philo			*philos_arr;
};

struct s_philo
{
	t_program		*program;
	pthread_t		philo_id;
	int				philo_index;
	int				last_eat;
	int				i_ate;
	pthread_mutex_t	last_eat_lock;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
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

enum e_ON_ERRROR_MODES
{
	CLEAN_RIGHT_FORK,
	CLEAN_BOTH
};
int		init_philo(t_program *program);
void	error_handler(int mode);
int		parse_and_check(int ac, char **av, t_program *original);
int		ft_atoi(const char *str, int *error_flag);
void	clean_all(t_program *program, int mode);

int		create_threads(t_program *program);
int		join_threads(t_program *program);
void	*observer_of_all(void *void_program);
int		check_dead(t_program *program);
void	clean_on_error(t_program *program, t_philo *philos_arr, int current);
void	*philo_routine(void *void_philo);
void	set_as_dead(t_program *program);
void	join_on_error(t_program *program, int current);

int		is_valid_av(int ac, char **av);
int		initialize_mutexes(t_program *program);
int		start_the_simulation(t_program *program);

time_t	get_time(void);
time_t	get_timestamp(t_program *program);
int		ft_usleep(size_t milliseconds, t_program *program);
void	limited_program(t_program *program, t_philo *philo);

int		print_thinking(t_philo *philo);
int		print_eating(t_philo *philo);
int		print_sleeping(t_philo *philo);
int		print_took_fork(t_philo *philo, int mode);
void	print_error(char *str);
#endif