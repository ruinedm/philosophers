#include "philo.h"

t_philo	*ft_lstnew_philo()
{
	t_philo	*new_philo;

	new_philo = malloc(sizeof(t_philo));
	if (!new_philo)
		return (NULL);
	return (new_philo);
}