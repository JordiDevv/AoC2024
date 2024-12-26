#include "../jslib.h"

void parse_input(int *n_rules, int *n_updates, int ***rules, int ***updates, int fd_input)
{
    *rules = malloc(sizeof(int*));
    char **split_line = ft_split(get_next_line(fd_input), '|');

    while (split_line && ft_strlen(split_line[0]) > 1)
    {
        (*n_rules)++;
        *rules = realloc(*rules, sizeof(int*) * (*n_rules));
        (*rules)[(*n_rules) - 1] = malloc(2 * sizeof(int));
        (*rules)[(*n_rules) - 1][0] = atoi(split_line[0]);
        (*rules)[(*n_rules) - 1][1] = atoi(split_line[1]);
        free_mat(split_line, 2);
        split_line = ft_split(get_next_line(fd_input), '|');
    }

    free_mat(split_line, 2);
    *updates = malloc(sizeof(int*));
    split_line = ft_split(get_next_line(fd_input), ',');

    while (split_line)
    {
        (*n_updates)++;
        *updates = realloc(*updates, sizeof(int*) * (*n_updates));
        int update_len = charmatlen(split_line);
        (*updates)[(*n_updates) - 1] = malloc(update_len * sizeof(int) + 4);
        for (int i = 0; i < update_len; i++)
            (*updates)[(*n_updates) - 1][i] = atoi(split_line[i]);
        (*updates)[(*n_updates) - 1][update_len] = 0;
        free_mat(split_line, 2);
        split_line = ft_split(get_next_line(fd_input), ',');
    }
}

int get_middle_update(int *updates)
{
    int i = 0;
    for (i; updates[i + 1]; i++);
    int middle = i / 2;
    return (updates[middle]);
}

int main()
{
    int fd_input = open("input_data.txt", O_RDONLY);
    if (fd_input < 0)
    {
        printf(R "Error opening the input file\n" RE);
        return (1);
    }

    int n_rules, n_updates = 0;
    int **rules, **updates = NULL;
    parse_input(&n_rules, &n_updates, &rules, &updates, fd_input);

    int result = 0;
    for (int i = 0; i < n_updates; i++)
    {
        int in_order = 1;
        for (int j = 0; updates[i][j + 1]; j++)
        {
            for (int k = 0; k < n_rules; k++)
            {
                if (rules[k][0] == updates[i][j + 1] && rules[k][1] == updates[i][j])
                {
                    in_order = 0;
                    int aux = updates[i][j];
                    updates[i][j] = updates[i][j + 1];
                    updates[i][j + 1] = aux;
                    j = 0;
                    break ;
                }
            }
        }
        if (!in_order)
            result += get_middle_update(updates[i]);
    }

    printf(G "%d\n" RE, result);
    return (0);
}