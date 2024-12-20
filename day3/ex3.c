#include "../jslib.h"

static int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

static int get_valid_n(char **beg, char **end, char *line, int **operands, int step, char lim)
{
    *beg = *end;
    for (int i = 0; i < 3; i++)
    {
        if (!ft_isdigit(**end))
            break ;
        (*end)++;
    }
    if (**end != lim)
        return (0);
    char *n = ft_substr(line, *beg - line, *end - *beg);
    (*operands)[step] = atoi(n);
    free(n);
    return (1);
}

static int get_line_result(char *line)
{
    char    *beg = line;
    int     result_line = 0;

    while (*beg)
    {
        int *operands = malloc(2 * sizeof(int));
        beg = ft_strchr(beg, 'm');
        if (!beg)
        {
            free(operands);
            return (result_line);
        }

        if (!ft_strncmp(beg, "mul(", 4))
        {
            char *end = beg + 4;
            if (!get_valid_n(&beg, &end, line, &operands, 0, ','))
                continue ;
            end++;
            if (!get_valid_n(&beg, &end, line, &operands, 1, ')'))
                continue ;
            result_line += operands[0] * operands[1];
            free(operands);
        }
        beg++;
    }
}

int main()
{
    int fd_input = open("input_data.txt", O_RDONLY);
    if (fd_input < 0)
    {
        printf(R "Error opening the data file\n" RE);
        return (1);
    }

    char    *line = get_next_line(fd_input);
    int     result = 0;

    while (line)
    {
        result += get_line_result(line);
        free(line);
        line = get_next_line(fd_input);
    }

    printf(G "%i" RE, result);
    return (0);
}