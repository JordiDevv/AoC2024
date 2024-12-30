#include "../jslib.h"

void exit_error(long **tests, int ***calibrations, char **split_line, char **split_calibrations,
                    int n_calibrations, int calibrations_len)
{
    if (*tests) free(*tests);
    if (*calibrations) free_imat(*calibrations, n_calibrations);
    if (split_line) free_cmat(split_line, 2);
    if (split_calibrations) free_cmat(split_calibrations, calibrations_len);
    printf(R "Error parsing input" RE);
    exit (EXIT_FAILURE);
}

void parse_input(long **tests, int ***calibrations, int fd_input, int *n_calibrations)
{
    *tests = malloc(sizeof(long));
    if (!(*tests)) exit_error(tests, calibrations, NULL, NULL, 0, 0);
    *calibrations = malloc(sizeof(int*));
    if (!(*calibrations)) exit_error(tests, calibrations, NULL, NULL, 1, 0);
    char **split_line = ft_split(get_next_line(fd_input), ':');
    if (!split_line) exit_error(tests, calibrations, split_line, NULL, 1, 1);
    char **split_calibrations = ft_split(split_line[1], ' ');
    if (!split_calibrations) exit_error(tests, calibrations, split_line, split_calibrations, 1, 1);
    int calibrations_len = charmatlen(split_calibrations);
    **calibrations = malloc(sizeof(int) * (calibrations_len + 1));
    if (!(**calibrations)) exit_error(tests, calibrations, split_line, split_calibrations, 1, 1);
    (**calibrations)[calibrations_len] = 0;
    
    int i;
    for (i = 1; split_line; i++)
    {
        (*tests)[i - 1] = atol(split_line[0]);
        *tests = realloc(*tests, sizeof(long) * (i + 1));
        if (!(*tests)) exit_error(tests, calibrations, split_line, split_calibrations, i, calibrations_len);

        for (int j = 0; j < calibrations_len; j++)
            (*calibrations)[i - 1][j] = atoi(split_calibrations[j]);
        (*calibrations)[i - 1][calibrations_len] = 0;
        *calibrations = realloc(*calibrations, sizeof(int*) * (i + 1));
        if (!(*calibrations)) exit_error(tests, calibrations, split_line, split_calibrations, i, calibrations_len);

        free_cmat(split_line, 2);
        free_cmat(split_calibrations, calibrations_len);
        split_line = ft_split(get_next_line(fd_input), ':');
        if (split_line) 
        {
            split_calibrations = ft_split(split_line[1], ' ');
            calibrations_len = charmatlen(split_calibrations);
            (*calibrations)[i] = malloc(sizeof(int) * (calibrations_len + 1));
        }
    }
    (*tests)[i] = 0;
    (*calibrations)[i] = NULL;
    *n_calibrations = i - 1;
}

bool calibrated_test(int *calibration, int calibration_len, long test_result)
{
    int posibilities = pow(2, calibration_len - 1);

    for (int mask = 0; mask < posibilities; mask++) 
    {
        long result = calibration[0];

        for (int i = 0; i < calibration_len - 1; i++) 
        {
            int operation = (mask >> i) & 1;

            result = operation == 0 ? result + calibration[i + 1] : result * calibration[i + 1];
        }

        if (result == test_result) return (true);
    }

    return (false);
}

long calibrate(int **calibrations, long *tests, int n_calibrations)
{
    long result = 0;

    for (int i = 0; i < n_calibrations; i++)
    {
        int calibration_len;
        for (calibration_len = 0; calibrations[i][calibration_len]; calibration_len++);
        if (calibrated_test(calibrations[i], calibration_len, tests[i]))
            result += tests[i];
    }

    return (result);
}

int main()
{
    int fd_input = open("input_data.txt", O_RDONLY);
    if (fd_input < 0)
    {
        printf(R "Error opening the input file\n" RE);
        return (1);
    }

    long *tests = NULL;
    int **calibrations = NULL;
    int n_calibrations = 0;
    parse_input(&tests, &calibrations, fd_input, &n_calibrations);

    long result = calibrate(calibrations, tests, n_calibrations);
    printf(G "%ld\n" RE, result);
    close(fd_input);
    return (0);
}