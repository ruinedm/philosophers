#include "philo.h"

t_philo	*ft_lstnew_philo(t_program *program, void *(routine)(void *), int index)
{
	t_philo	*new_philo;

	new_philo = malloc(sizeof(t_philo));
	if (!new_philo)
		return (NULL);
	pthread_create(&new_philo->philo_id, NULL, routine, (void *)program);
	new_philo->philo_index = index;
	new_philo->has_already_eaten = FALSE;
	new_philo->next = NULL;
	new_philo->prev = NULL;
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
	t_philo	*tmp;
	int i;

	i = 0;
	while (i < philo_count)
	{
		tmp = lst->next;
		if (mode == JOIN_THREADS)
			pthread_join(lst->philo_id, NULL);
		else if (mode == INITIALIZE_MUTEXES)
			pthread_mutex_init(&lst->my_fork, NULL);
		lst = tmp;
		i++;
	}
}