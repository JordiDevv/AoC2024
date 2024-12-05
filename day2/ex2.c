#include "../jslib.h"

static void get_next_line_splited(int input_fd, char ***split_line)
{
    char    *line = NULL;

    line = get_next_line(input_fd);
    if (!line)
    {
        printf(R "Error getting next line" RE);
        exit(EXIT_FAILURE);
    }
    *split_line = ft_split(line, ' ');
    free(line);
    if (!*split_line)
    {
        printf(R "Error spliting one line" RE);
        exit(EXIT_FAILURE);
    }
}

static int cast_line(int **report, char **split_line)
{
    int i = 0;
    int len = 0;

    for (int i = 0; split_line[i]; i++)
        len++;
    *report = malloc(len * 4);
    for (int i = 0; split_line[i]; i++)
        (*report)[i] = atoi(split_line[i]);

    return (len);
}

static int check_report(int *report, int len)
{
    int i = 0;
    int asc_flag = 0;
    int problem_dampener = 1;
    if ((report[i + 1] - report[i] > 0 && report[i + 2] - report[i + 1] > 0)
            || (report[i + 1] - report[i] > 0 && report[i + 3] - report[i + 2] > 0))
        asc_flag = 1;
    
    int diff = report[i + 1] - report[i];
    if (!((diff > 0 && diff < 4 && asc_flag) || (diff < 0 && diff > -4 && !asc_flag))
            || diff == 0)
    {
        i++;
        problem_dampener--;
    }

    while (i < len - 1)
    {
        if (i >= len - 2 && problem_dampener)
            return (1);
        diff = report[i + 1] - report[i];
        if (!((diff > 0 && diff < 4 && asc_flag) || (diff < 0 && diff > -4 && !asc_flag)))
        {
            if (problem_dampener)
            {
                diff = report[i + 2] - report[i];
                if ((diff > 0 && diff < 4 && asc_flag) || (diff < 0 && diff > -4 && !asc_flag))
                {
                    i += 2;
                    problem_dampener--;
                    continue ;
                }
                diff = report[i + 1] - report[i - 1];
                if ((diff > 0 && diff < 4 && asc_flag) || (diff < 0 && diff > -4 && !asc_flag))
                {
                    i += 2;
                    problem_dampener--;
                    continue ;
                }
                else
                    return (0);
            }
            else
                return (0);
        }
        i++;
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
    int     *report;
    int     i = 0;
    int     safe_reports = 0;

    while (i < 1000)
    {
        get_next_line_splited(input_fd, &split_line);
        int len = cast_line(&report, split_line);
        i++;
        free_mat(split_line, len);
        safe_reports += check_report(report, len);
        free(report);
    }

    printf(G "%i\n" RE, safe_reports);
    return (0);
}