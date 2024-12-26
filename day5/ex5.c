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
        (*updates)[(*n_updates) - 1] = malloc(update_len * sizeof(int));
        for (int i = 0; i < update_len; i++)
            (*updates)[(*n_updates) - 1][i] = atoi(split_line[i]);
        free_mat(split_line, 2);
        split_line = ft_split(get_next_line(fd_input), ',');
    }
}

int main()
{
    int fd_input = open("input_data_prueba.txt", O_RDONLY);
    if (fd_input < 0)
    {
        printf(R "Error opening the input file\n" RE);
        return (1);
    }

    int n_rules, n_updates = 0;
    int **rules, **updates = NULL;
    parse_input(&n_rules, &n_updates, &rules, &updates, fd_input);

}