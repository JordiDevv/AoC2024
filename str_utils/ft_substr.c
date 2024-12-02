#include "../jslib.h"

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*subs;

	if (ft_strlen(s) <= start)
		return (ft_calloc(1, 1));
	if (ft_strlen(s) - start < len)
		len = ft_strlen(s) - start;
	subs = malloc(len + 1);
	if (!subs)
		return (0);
	ft_strlcpy(subs, s + start, len + 1);
	return (subs);
}
