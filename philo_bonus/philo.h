/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboukour <mboukour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 08:26:34 by mboukour          #+#    #+#             */
/*   Updated: 2024/07/18 22:25:22 by mboukour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <semaphore.h>
# include <unistd.h>
# include <limits.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <signal.h>

typedef int					t_bool;
typedef struct s_philo		t_philo;
typedef struct s_program	t_program;

struct s_program
{
	sem_t	*forks;
	sem_t	*print_sem;
	int		is_locked;
	int		philo_count;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		philos_done_eating;
	time_t	start_timestamp;
	t_bool	is_limited;
	int		number_of_eat;
	int		observer_sleep;
	t_philo	*philos_arr;
};

struct s_philo
{
	pthread_t	philo_observer;
	t_program	*program;
	pid_t		philo_id;
	int			philo_index;
	int			last_eat;
	int			eat_count;
	char		*last_eat_str;
	sem_t		*last_eat_sem;
};

enum e_ERROR_MODES
{
	INPUT_ERROR,
	TIME_ERROR,
	MALLOC_ERROR,
	CREATE_THREAD_ERROR,
	JOIN_THREAD_ERROR,
	MUTEX_INIT_ERROR,
	PROCESS_FATAL_ERROR
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

enum e_EXIT_STATUS
{
	DEAD_PHILO=2,
	EATEN_ENOUGH
};

void	first_sems(t_program *program);
void	kill_on_error(t_program *program, int until);
void	clean_all(t_program *program);
void	error_handler(int mode);
int		parse_and_check(int ac, char **av, t_program *original);
int		ft_atoi(const char *str, int *error_flag);
void	init_philo(t_program *program);
void	*observer_of_all(void *void_program);
int		check_dead(t_program *program);
void	exit_procedure(int status, t_program *program);
void	set_as_dead(t_program *program);
char	*ft_strjoin(const char *s1, const char *s2);
char	*ft_itoa(int n);

void	create_thread_error(t_program *program, int i);
int		create_threads(t_program *program);
int		join_threads(t_program *program);

time_t	get_time(void);
time_t	get_timestamp(t_program *program);
int		ft_usleep(size_t milliseconds);

void	pick_up_fork(t_program *program, t_philo *philo);
void	eat_and_put_down_forks(t_program *program, t_philo *philo);
void	sleep_think_philo(t_program *program, t_philo *philo);
void	print_error(char *str);
void	init_philo(t_program *program);

void	observe_philos(t_program *program);
void	kill_all(t_program *program, int already_dead);

int		ft_abs(int a);
#endif