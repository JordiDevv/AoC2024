#include "../jslib.h"

void exit_error(int **tests, int ***calibrations, char **split_line, char **split_calibrations,
                    int n_calibrations, int calibrations_len)
{
    if (*tests) free(*tests);
    if (*calibrations) free_imat(*calibrations, n_calibrations);
    if (split_line) free_cmat(split_line, 2);
    if (split_calibrations) free_cmat(split_calibrations, calibrations_len);
    printf(R "Error parsing input" RE);
    exit (EXIT_FAILURE);
}

void parse_input(int **tests, int ***calibrations, int fd_input)
{
    *tests = malloc(sizeof(int));
    if (!(*tests)) exit_error(tests, calibrations, NULL, NULL, 0, 0);
    *calibrations = malloc(sizeof(int*));
    if (!(*calibrations)) exit_error(tests, calibrations, NULL, NULL, 1, 0);
    char **split_line = ft_split(get_next_line(fd_input), ':');
    if (!split_line) exit_error(tests, calibrations, split_line, NULL, 1, 1);
    char **split_calibrations = ft_split(split_line[1], ' ');
    if (!split_calibrations) exit_error(tests, calibrations, split_line, split_calibrations, 1, 1);
    int calibrations_len = charmatlen(split_calibrations);
    **calibrations = malloc(sizeof(int) * (calibrations_len + 1));
    if (!(**calibrations)) exit_error(tests, calibrations, split_line, split_calibrations, 1, 1);
    (**calibrations)[calibrations_len] = 0;
    
    int i;
    for (i = 1; split_line; i++)
    {
        (*tests)[i - 1] = atoi(split_line[0]);
        *tests = realloc(*tests, sizeof(int) * (i + 1));
        if (!(*tests)) exit_error(tests, calibrations, split_line, split_calibrations, i, calibrations_len);

        for (int j = 0; j < calibrations_len; j++)
            (*calibrations)[i - 1][j] = atoi(split_calibrations[j]);
        (*calibrations)[i - 1][calibrations_len] = 0;
        *calibrations = realloc(*calibrations, sizeof(int*) * (i + 1));
        if (!(*calibrations)) exit_error(tests, calibrations, split_line, split_calibrations, i, calibrations_len);

        free_cmat(split_line, 2);
        free_cmat(split_calibrations, calibrations_len);
        split_line = ft_split(get_next_line(fd_input), ':');
        if (split_line) 
        {
            split_calibrations = ft_split(split_line[1], ' ');
            calibrations_len = charmatlen(split_calibrations);
            (*calibrations)[i] = malloc(sizeof(int) * (calibrations_len + 1));
        }
    }
    (*tests)[i] = 0;
    (*calibrations)[i] = NULL;
}

int main()
{
    int fd_input = open("input_data_prueba.txt", O_RDONLY);
    if (fd_input < 0)
    {
        printf(R "Error opening the input file\n" RE);
        return (1);
    }

    int *tests = NULL;
    int **calibrations = NULL;
    parse_input(&tests, &calibrations, fd_input);
}