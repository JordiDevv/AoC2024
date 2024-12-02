#include "ex1.1.h"

int comp_lists(int *left_list, int *right_list)
{
	int i = 0;
	int total = 0;

	while (i < 1000)
	{
		int diff = left_list[i] - right_list[i];
		if (diff < 0)
			diff *= -1;
		total += diff;
		i++;
	}

	return (total);
}

void sort_list(int *list)
{
	int	i = 1;
	int	aux = 0;

	while (i < 1000)
	{
		int j = i;
		while (list[j] < list[j - 1])
		{
			aux = list[j];
			list[j] = list[j - 1];
			list[j - 1] = aux;
			if (j > 1)
				j--;
			else
				break ;
		}
		i++;
	}
}

void fill_lists(int *left_list, int *right_list, int lst_fd)
{
	int		i = 0;
	char	*line = NULL;
	char	**split_line = NULL;

	while (i < 1000)
	{
		line = get_next_line(lst_fd);
		if (!line)
		{
			printf (R "Error getting one line" RE);
			exit (EXIT_FAILURE);
		}
		split_line = ft_split(line, ' ');
		if (!split_line)
		{
			printf (R "Error spliting one line" RE);
			if (line)
				free (line);
			exit (EXIT_FAILURE);
		}
		free (line);
		left_list[i] = atoi(split_line[0]);
		right_list[i] = atoi(split_line[1]);
		free (split_line[0]);
		free (split_line[1]);
		free (split_line);
		i++;
	}
}

int main()
{
    int	*left_list = malloc(1000 * sizeof(int) + 1);
	if (!left_list)
	{
		printf(R "Error allocating memory for the left list" RE);
		return (1);
	}
	int	*right_list = malloc(1000 * sizeof(int) + 1);
	if (!right_list)
	{
		printf(R "Error allocating memory for the right list" RE);
		return (1);
	}
    int		lst_fd = open("input_list.txt", O_RDONLY);
    if (lst_fd < 0)
    {
        printf(R "Error: Couldn't open the list file" RE);
        return (1);
    }

    fill_lists(left_list, right_list, lst_fd);
	sort_list(left_list);
	sort_list(right_list);
	printf("%i", comp_lists(left_list, right_list));

	return (0);
}