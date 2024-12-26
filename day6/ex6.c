#include "../jslib.h"

typedef struct s_guard_data
{
    int     x;
    int     y;
    char    dir;
}   guard_data;

char **parse_map(int input_fd)
{
    char *line = get_next_line(input_fd);
    if (!line)
    {
        printf(R "Error parsing one line\n" RE);
        exit (EXIT_FAILURE);
    }
    char **map = malloc(sizeof(char*) + 1);
    if (!map)
    {
        printf(R "Error allocating memory for the map\n" RE);
        exit (EXIT_FAILURE);
    }
    int height = 0;

    while (line)
    {
        height++;
        map = realloc(map, sizeof(char*) * height + 1);
        if (!map)
        {
            printf(R "Error allocating memory for the map\n" RE);
            exit (EXIT_FAILURE);
        }
        map[height - 1] = malloc(sizeof(char) * ft_strlen(line) + 1);
        if (!map[height - 1])
        {
            printf(R "Error allocating memory for the map\n" RE);
            exit (EXIT_FAILURE);
        }
        ft_strlcpy(map[height - 1], line, ft_strlen(line));
        line = get_next_line(input_fd);
    }
    map[height] = NULL;

    return (map);
}

void init_guard_data(guard_data **guard, char **map)
{
    for (int i = 0; map[i]; i++)
    {
        for (int j = 0; map[i][j]; j++)
        {
            if (map[i][j] == '^' || map[i][j] == '>' || map[i][j] == '<'
                    || map[i][j] == 'v')
            {
                (*guard)->x = j;
                (*guard)->y = i;
                (*guard)->dir = map[i][j];
            }
        }
    }
}

int main()
{
    int input_fd = open("input_map_prueba.txt", O_RDONLY);
    if (input_fd < 0)
    {
        printf(R "Error opening the map file\n" RE);
        return (1);
    }

    char **map = parse_map(input_fd);

    guard_data *guard = malloc(sizeof(guard_data));
    init_guard_data(&guard, map);
    printf("x = %d\ny = %d\ndir = %c\n", guard->x, guard->y, guard->dir);
}