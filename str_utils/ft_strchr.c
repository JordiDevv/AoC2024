#include "../jslib.h"

char	*ft_strchr(char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return (&((char *)s)[i]);
		i++;
	}
	if ((char)c == 0)
		return (&((char *)s)[i]);
	return (0);
}

char	*ft_strrchr(const char *s, int c)
{
	char	*r;

	r = (char *)s;
	while (*s)
		s++;
	while (s >= r)
	{
		if (*s == (char)c)
			return ((char *)s);
		s--;
	}
	return (NULL);
}