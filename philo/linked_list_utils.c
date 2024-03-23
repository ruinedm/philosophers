#include "philo.h"

t_philo	*ft_lstnew_philo(t_program *program, void *(routine)(void *), int index)
{
	t_philo	*new_philo;

	new_philo = malloc(sizeof(t_philo));
	if (!new_philo)
		return (NULL);
	pthread_create(&new_philo->philo_id, NULL, routine, (void *)program);
	new_philo->philo_index = index;
	new_philo->next = NULL;
	return (new_philo);
}

t_philo	*ft_lstlast(t_philo *lst)
{
	while (lst->next)
		lst = lst->next;
	return (lst);
}
void	ft_lstadd_back(t_philo **lst, t_philo *new)
{
	if (!*lst)
		*lst = new;
	else
		ft_lstlast(*lst)->next = new;
}
void	ft_lstiter_join(t_philo *lst)
{
	t_philo	*tmp;

	while (lst != NULL)
	{
		tmp = lst->next;
		pthread_join(lst->philo_id, NULL);
		lst = tmp;
	}
}