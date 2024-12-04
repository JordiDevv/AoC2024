#include "../jslib.h"

static void get_next_line_splited(int input_fd, char **split_line)
{
    char    *line = NULL;

    line = get_next_line(input_fd);
    if (!line)
    {
        printf(R "Error getting next line" RE);
        exit(EXIT_FAILURE);
    }
    split_line = ft_split(line, ' ');
    free(line);
    if (!split_line)
    {
        printf(R "Error spliting one line" RE);
        exit(EXIT_FAILURE);
    }
}

static int check_report(char **split_line)
{
    int i = 0;
    int asc_flag = 0;
    if (split_line[i + 1] - split_line[i] > 0)
        asc_flag = 1;

    while (split_line[i + 1])
    {
        int diff = split_line[i + 1] - split_line[i];
        if ((diff > 0 && diff < 4 && asc_flag) || (diff < 0 && diff > -4 && !asc_flag))
            i++;
        else
            return (0);
    }
    return (1);
}

int main()
{
    int		input_fd = open("input_list.txt", O_RDONLY);
    if (input_fd < 0)
    {
        printf(R "Error: Couldn't open the list file\n" RE);
        return (1);
    }

    char    **split_line = NULL;
    int     i = 0;
    int     safe_reports = 0;

    while (i < 1000)
    {
        get_next_line_splited(input_fd, split_line);
        safe_reports += check_report(split_line);
        i++;
        free_mat(split_line, i);
    }

    printf(G "%i\n" RE, safe_reports);
    return (0);
}