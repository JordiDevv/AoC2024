#include "ex1.1.h"

/*t_list *create_node(char *value, int index)
{
	t_list	*node;

	node->value = (int)value;
	node->index = index;
	node->prev = NULL;
	node->next = NULL;

	return (node);
}

void append_node(t_list *list, char *value, int index)
{
	list->next = create_node(value, index);
	list->next->prev = list;
	list = list->next;
}

t_list **init_lists(int lst_fd, t_list **lists)
{
    char	*line = NULL;
	char	**split_line = NULL;
	int		i = 1;

	line = get_next_line(lst_fd);
	split_line = split(line, ' ');
	lists[0] = create_node(split_line[0], i);
	lists[1] = create_node(split_line[1], i);
	t_list	*left_head = lists[0];
	t_list	*right_head = lists[1];
	i++;

	while (line)
	{
		free (line);
		line = get_next_line(lst_fd);
		if (!line)
			break ;
		free(split_line[0]);
		free(split_line[1]);
		free(split_line);
		split_line = split(line, ' ');
		append_node(lists[0], split_line[0], i);
		append_node(lists[1], split_line[1], i);
		i++;
	}

	lists[0] = left_head;
	lists[1] = right_head;
	return(lists);

}*/

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
	printf("%i, %i", left_list[0], right_list[1]);
	return (0);
}