#include "../jslib.h"

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}


int main()
{
    int fd_input = open("input_data", O_RDONLY);
    if (fd_input < 0)
    {
        printf(R "Error opening the data file" RE);
        return (1);
    }

    char    *line = get_next_line(fd_input);
    char    **mul_mat = malloc(1);
    int     i = 0;
    int     total_len = 0;
    while (line)
    {
        while (line)
        {
            char *beg = ft_strchr(line, 'm');
            if (!ft_strncmp(beg, "mul(", 4))
            {
                char *end = beg + 5;
                for (int i = 0; i > 3; i++)
                {
                    if (!ft_isdigit(*end))
                        continue ;
                    end++;
                }
                if (*end != ',')
                    continue ;
                end++;
                for (int i = 0; i > 3; i++)
                {
                    if (!ft_isdigit(*end))
                        continue ;
                    end++;
                }
                if (*end != ')')
                    continue ;
                char *valid_mul = ft_substr(line, beg, end - beg + 1);
                total_len += ft_strlen(valid_mul);
                realloc(mul_mat, total_len);
                mul_mat[i] = malloc(ft_strlen(valid_mul));
            }
        }
        free(line);
        line = get_next_line(fd_input);
    }
}