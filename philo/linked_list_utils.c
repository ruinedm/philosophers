#include "philo.h"

t_philo	*ft_lstnew_philo(t_program *program, void *(routine)(void *), int index)
{
	t_philo	*new_philo;

	new_philo = malloc(sizeof(t_philo));
	if (!new_philo)
		return (NULL);
	new_philo->philo_index = index;
	new_philo->has_already_eaten = FALSE;
	new_philo->right_fork = malloc(sizeof(pthread_mutex_t));
	if(!new_philo->right_fork)
	{
		free(new_philo);
		return (NULL);
	}
	new_philo->program = program;
	pthread_mutex_init(new_philo->right_fork, NULL);
	new_philo->left_fork= NULL;
	new_philo->next = NULL;
	new_philo->prev = NULL;
	pthread_create(&new_philo->philo_id, NULL, routine, new_philo);
	return (new_philo);
}

t_philo	*ft_lstlast(t_philo *lst)
{
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void ft_lstadd_back(t_philo **lst, t_philo *new)
{
	t_philo *last;

    if (!*lst) 
        *lst = new;
    else 
	{
        last = ft_lstlast(*lst);
        last->next = new;
        new->prev = last;
        new->next = NULL;
    }
}

void	ft_lstiter_philo(t_philo *lst, int mode, int philo_count)
{
	t_philo	*original;
	int i;

	i = 0;
	original = lst;
	while (i < philo_count)
	{
		if (mode == JOIN_THREADS)
			pthread_join(lst->philo_id, NULL);
		else if (mode == LOCK_FORKS)
			pthread_mutex_lock(lst->right_fork);
		else if (mode == SETUP_LEFT_FORK)
		{
			if(i == philo_count - 1)
				lst->left_fork = original->right_fork;
			else
				lst->left_fork = lst->next->right_fork;
		}
		lst = lst->next;
		i++;
	}
}