#include "../jslib.h"

void parse_input(int **tests, int ***calibrations, int fd_input)
{
    *tests = malloc(sizeof(int));
    *calibrations = malloc(sizeof(int*));
    char **split_line = ft_split(get_next_line(fd_input), ':');
    char **split_calibrations = ft_split(split_line[1], ' ');
    int calibrations_len = charmatlen(split_calibrations);
    int i;

    //Ahora falta implementar la lógica en el bucle para que vaya actualizando "calibrations".
    for (i = 1; split_line; i++)
    {
        (*tests)[i - 1] = atoi(split_line[0]);
        *tests = realloc(*tests, sizeof(int) * (i + 1));
    }
    (*tests)[i] = 0;
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