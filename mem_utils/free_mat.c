#include "../jslib.h"

void	free_mat(char **mat, int i)
{
	if (mat)
	{
		while (i > 0)
			free (mat[--i]);
		free (mat);
		mat = NULL;
	}
}
