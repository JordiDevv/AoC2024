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

    return (0);
}