#include "../jslib.h"

static int get_n_lines()
{
    int fd_pipe[2];
    if (pipe(fd_pipe) == -1)
    {
        printf(R "Error creating the pipe for parse_mat" RE);
        exit (1);
    }

    int pid = fork();
    if (pid == 0)
    {
        int child_fd_input = open("input_data_prueba.txt", O_RDONLY);
        if (child_fd_input < 0)
        {
            printf(R "Error opening the data file in the child process\n" RE);
            return (1);
        }

        close(fd_pipe[0]);
        char *line = get_next_line(child_fd_input);
        int lines_counter = 0;
        while (line)
        {
            lines_counter++;
            free(line);
            line = get_next_line(child_fd_input);
        }
        write(fd_pipe[1], &lines_counter, sizeof(lines_counter));
        close(child_fd_input);
        exit(EXIT_SUCCESS);
    }

    wait(NULL);
    int n_lines;
    read(fd_pipe[0], &n_lines, sizeof(n_lines));
    return (n_lines);
}

static char **parse_input(int fd_input, int n_lines)
{
    char *line = get_next_line(fd_input);
    char **input_mat = malloc((n_lines + 1) * sizeof(char *));

    for (int i = 0; line; i++)
    {
        input_mat[i] = malloc(ft_strlen(line) + 1);
        ft_strlcpy(input_mat[i], line, ft_strlen(line) + 1);
        free(line);
        line = get_next_line(fd_input);
    }

    input_mat[n_lines] = NULL;
    return (input_mat);
}

static int check_xmas(char **input_mat, char *x_inst, int i, int j, int n_lines, int len)
{
    int return_value = 0;
    int pos[2];
    pos[0] = i;
    pos[1] = j;

    //La idea es buscar la instancia necesaria en bucle, en todas direcciones, y que la \
        función dedicada a eso devuelva un puntero que se almacenará en pos para buscar a \
        partir de ahí la siguiente letra; o quizás se haga toda la búsqueda en una función \
        auxiliar.
    if (len - j >= 4)
    {
        if (ft_strchr(ft_strchr(ft_strchr(x_inst, 'M'), 'A'), 'S'))
            return_value++;
            
    }
    /*if (n_lines - i >= 4)
    {
        if (input_mat[i + 1][j] == 'M' && input_mat[i + 2][j] == 'A' && input_mat[i + 3][j] == 'S')
            return_value++;
    }
    */if (j >= 3)
    {
        if (ft_strrnchr(input_mat[i], 'S', ft_strrnchr(input_mat[i], 'A', ft_strrnchr(input_mat[i], 'M', x_inst))))
            return_value++;
    }
    /*if (i >= 3)
    {
        if (input_mat[i - 1][j] == 'M' && input_mat[i - 2][j] == 'A' && input_mat[i - 3][j] == 'S')
            return_value++;
    }
    if (len - j >= 4 && n_lines - i >= 4)
    {
        if (input_mat[i + 1][j + 1] == 'M' && input_mat[i + 2][j + 2] == 'A' && input_mat[i + 3][j + 3] == 'S')
            return_value++;
    }
    if (j >= 4 && n_lines - i >= 4)
    {
        if (input_mat[i + 1][j - 1] == 'M' && input_mat[i + 2][j - 2] == 'A' && input_mat[i + 3][j - 3] == 'S')
            return_value++;
    }
    if (j >= 4 && i >= 4)
    {
        if (input_mat[i - 1][j - 1] == 'M' && input_mat[i - 2][j - 2] == 'A' && input_mat[i - 3][j - 3] == 'S')
            return_value++;
    }
    if (len - j >= 4 && i >= 4)
    {
        if (input_mat[i - 1][j + 1] == 'M' && input_mat[i - 2][j + 2] == 'A' && input_mat[i - 3][j + 3] == 'S')
            return_value++;
    }*/

    return (return_value);
}

int main()
{
    int fd_input = open("input_data_prueba.txt", O_RDONLY);
    if (fd_input < 0)
    {
        printf(R "Error opening the data file\n" RE);
        return (1);
    }

    int n_lines = get_n_lines();
    char **input_mat = parse_input(fd_input, n_lines);
    int len = ft_strlen(input_mat[0]) - 1;

    int xmas_instances = 0;
    for (int i = 0; input_mat[i]; i++)
    {
        for (int j = 0; input_mat[i][j]; j++)
            if (input_mat[i][j] == 'X') xmas_instances += check_xmas(input_mat, &input_mat[i][j], i, j, n_lines, len);
    }

    printf(G "XMAS instances: %i\n" RE, xmas_instances);
    return (0);
}