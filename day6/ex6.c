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

int move_guard(guard_data **guard, char **map)
{
    int cells_check = 0;
    int i = 0;

    if ((*guard)->dir == '^')
    {
        for (i = (*guard)->y; map[i - 1][(*guard)->x] && map[i - 1][(*guard)->x] != '#'; i--)
            cells_check++;
        if (map[i - 1][(*guard)->x] == '#')
            (*guard)->dir = '>';
        (*guard)->y = i;
    }
    else if ((*guard)->dir == '>')
    {
        for (i = (*guard)->x; map[(*guard)->y][i + 1] && map[(*guard)->y][i + 1] != '#'; i++)
            cells_check++;
        if (map[(*guard)->y][i + 1] == '#')
            (*guard)->dir = 'v';
        (*guard)->x = i;
    }
    else if ((*guard)->dir == 'v')
    {
        for (i = (*guard)->y; map[i + 1][(*guard)->x] && map[i + 1][(*guard)->x] != '#'; i++)
            cells_check++;
        if (map[i + 1][(*guard)->x] == '#')
            (*guard)->dir = '<';
        (*guard)->y = i;
    }
    else
    {
        for (i = (*guard)->x; map[(*guard)->y][i - 1] && map[(*guard)->y][i - 1] != '#'; i--)
            cells_check++;
        if (map[(*guard)->y][i - 1] == '#')
            (*guard)->dir = '^';
        (*guard)->x = i;
    }

    return (cells_check);
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
    
    int cells_check = 1;
    while(1)
    {
        if ((guard->dir == '^' && !map[guard->y - 1][guard->x]) || (guard->dir == '>' && !map[guard->y][guard->x + 1])
                || (guard->dir == '<' && !map[guard->y][guard->x - 1]) || (guard->dir == 'v' && !map[guard->y + 1][guard->x]))
            break ;
        printf("%d\n", cells_check);
        cells_check += move_guard(&guard, map);
    }

    printf(G "%d\n" RE, cells_check);
    return (0);
}