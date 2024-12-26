#include "../jslib.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	charmatlen(char **mat)
{
	if (!mat)
		return (0);
	int i = 0;
	for (i; mat[i]; i++);
	return (i);
}