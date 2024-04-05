#include "philo.h"

size_t	ft_strlen(const char *s)
{
	size_t	length;

	length = 0;
	while (*s)
	{
		length++;
		s++;
	}
	return (length);
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*finalstr;
	int		i;
	int		j;

	// if (!s1 || !s2)
	// 	return (ft_strdup(""));
	i = 0;
	j = 0;
	finalstr = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1)
			* sizeof(char));
	if (!finalstr)
		return (NULL);
	while (s1[i])
		finalstr[j++] = s1[i++];
	i = 0;
	while (s2[i])
	{
		finalstr[j] = s2[i];
		j++;
		i++;
	}
	finalstr[j] = 0;
	return (finalstr);
}