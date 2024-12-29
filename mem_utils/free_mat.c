#include "../jslib.h"

void	free_cmat(char **mat, int i)
{
	if (mat)
	{
		while (i > 0)
			free (mat[--i]);
		free (mat);
		mat = NULL;
	}
}

void	free_imat(int **mat, int i)
{
	if (mat)
	{
		while (i > 0)
			free (mat[--i]);
		free (mat);
		mat = NULL;
	}
}
