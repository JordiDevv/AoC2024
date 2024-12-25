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