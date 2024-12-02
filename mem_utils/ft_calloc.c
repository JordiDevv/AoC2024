#include "../jslib.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;
	size_t	t_size;

	t_size = count * size;
	ptr = malloc(t_size);
	if (ptr == NULL)
		return (NULL);
	ft_bzero(ptr, t_size);
	return (ptr);
}
