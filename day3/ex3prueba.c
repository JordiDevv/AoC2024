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
    char    *do_line = NULL;
    int     enabled = 1;
    int     flag = 0;

    while (line)
    {
        char *end = line;
        while (line)
            end++;
        char *beg = end;
        while (beg > line)
        {
            if (!ft_strrchr(beg, 'd'))
            {
                if (ft_strncmp(beg, "don't()", 7))
                {
                    end = beg;
                    while (*end)
                    {
                        if (!ft_strchr(end, 'd'))
                        {
                            if (ft_strncmp(end, "do()", 4))
                            {
                                char *aux_beg = end;
                                
                            }
                        }
                    }

                }
            }
            beg--;
        }
        do_line = ft_substr(line, beg - line, end - beg);
        result += get_line_result(do_line);

        free(line);
        line = get_next_line(fd_input);
    }

    printf(G "%i" RE, result);
    return (0);
}