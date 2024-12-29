#include "../jslib.h"

typedef struct s_guard_data
{
    int     x;
    int     y;
    char    dir;
    bool    end;
}   guard_data;

char **parse_map(int input_fd)
{
    char *line = get_next_line(input_fd);
    if (!line)
    {
        printf(R "Error parsing one line\n" RE);
        exit (EXIT_FAILURE);
    }
    char **map = malloc(sizeof(char*));
    if (!map)
    {
        printf(R "Error allocating memory for the map\n" RE);
        exit (EXIT_FAILURE);
    }
    int height = 0;

    while (line)
    {
        height++;
        map = realloc(map, sizeof(char*) * (height + 1));
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
    (*guard)->end = false;
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
        for (i = (*guard)->y; i > 0 && map[i - 1][(*guard)->x] != '#'; i--)
            map[i][(*guard)->x] = 'X';
        map[i][(*guard)->x] = 'X';
        if (i <= 0)
            ((*guard))->end = true;
        (*guard)->dir = '>';
        (*guard)->y = i;
    }
    else if ((*guard)->dir == '>')
    {
        for (i = (*guard)->x; map[(*guard)->y][i + 1] && map[(*guard)->y][i + 1] != '#'; i++)
            map[(*guard)->y][i] = 'X';
        map[(*guard)->y][i] = 'X';
        if (!map[(*guard)->y][i + 1])
            ((*guard))->end = true;
        (*guard)->dir = 'v';
        (*guard)->x = i;
    }
    else if ((*guard)->dir == 'v')
    {
        for (i = (*guard)->y; map[i + 1] && map[i + 1][(*guard)->x] != '#'; i++)
            map[i][(*guard)->x] = 'X';
        map[i][(*guard)->x] = 'X';
        if (!map[i + 1])
            ((*guard))->end = true;
        (*guard)->dir = '<';
        (*guard)->y = i;
    }
    else
    {
        for (i = (*guard)->x; i > 0 && map[(*guard)->y][i - 1] != '#'; i--)
            map[(*guard)->y][i] = 'X';
        map[(*guard)->y][i] = 'X';
        if (i <= 0)
            ((*guard))->end = true;
        (*guard)->dir = '^';
        (*guard)->x = i;
    }

    return (cells_check);
}

int count_cells(char **map)
{
    int cells_check = 0;

    for (int i = 0; map[i]; i++)
    {
        for (int j = 0; map[i][j]; j++)
            if (map[i][j] == 'X') cells_check++;
    }

    return (cells_check);
}

int main()
{
    int input_fd = open("input_map.txt", O_RDONLY);
    if (input_fd < 0)
    {
        printf(R "Error opening the map file\n" RE);
        return (1);
    }

    char **map = parse_map(input_fd);

    guard_data *guard = malloc(sizeof(guard_data));
    init_guard_data(&guard, map);
    
    while(1)
    {
        if (guard->end) break ;
        move_guard(&guard, map);
    }
    int cells_check = count_cells(map);

    printf(G "%d\n" RE, cells_check);
    return (0);
}