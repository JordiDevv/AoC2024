#include "../jslib.h"

static int similarity_score(int *left_list, int *right_list)
{
	int i = 0;
	int total = 0;

	while (i < 1000)
	{
		int j = 0;
		int similarity = 0;
		while(j < 1000)
		{
			if (left_list[i] == right_list[j])
				similarity++;
			j++;
		}
		total += left_list[i] * similarity;
		i++;
	}

	return (total);
}

static int comp_lists(int *left_list, int *right_list)
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

static void sort_list(int *list)
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

static void fill_lists(int *left_list, int *right_list, int lst_fd)
{
	int		i = 0;
	char	*line = NULL;
	char	**split_line = NULL;

	while (i < 1000)
	{
		line = get_next_line(lst_fd);
		if (!line)
		{
			printf (R "Error getting one line\n" RE);
			exit (EXIT_FAILURE);
		}
		split_line = ft_split(line, ' ');
		if (!split_line)
		{
			printf (R "Error spliting one line\n" RE);
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

int main(int argc, char **argv)
{
	if (argc != 2 || (argv[1][0] != '1' && argv[1][0] != '2') || ft_strlen(argv[1]) != 1)
	{
		printf(R "Please, type 1 or 2 as argument for the program\n" RE);
		return (0);
	}
    int	*left_list = malloc(1000 * sizeof(int) + 1);
	if (!left_list)
	{
		printf(R "Error allocating memory for the left list\n" RE);
		return (1);
	}
	int	*right_list = malloc(1000 * sizeof(int) + 1);
	if (!right_list)
	{
		printf(R "Error allocating memory for the right list\n" RE);
		return (1);
	}
    int		lst_fd = open("input_list.txt", O_RDONLY);
    if (lst_fd < 0)
    {
        printf(R "Error: Couldn't open the list file\n" RE);
        return (1);
    }

    fill_lists(left_list, right_list, lst_fd);
	sort_list(left_list);
	sort_list(right_list);

	int diff = comp_lists(left_list, right_list);
	int similarity = similarity_score(left_list, right_list);

	if (argv[1][0] == '1')
		printf("%i\n", diff);
	else if (argv[1][0] == '2')
		printf("%i\n", similarity);

	return (0);
}