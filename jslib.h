#ifndef JSLIB_H
# define JSLIB_H

# define G "\033[32m"
# define R "\033[31m"
# define Y "\033[33m"
# define RE "\033[0m"

# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <sys/wait.h>
# include <stdbool.h>
# include "get_next_line/get_next_line.h"

void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t count, size_t size);
void	*ft_memset(void *b, int c, size_t len);
void	free_mat(char **mat, int i);

char	**ft_split(char const *s, char c);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_strlen(const char *s);
int	charmatlen(char **mat);
char	*ft_substr(const char *s, unsigned int start, size_t len);
char    *ft_strchr(char *s, int c);
char	*ft_strrchr(const char *s, int c);
char	*ft_strrnchr(const char *s, int c, char *beg);
int     ft_strncmp(const char *s1, const char *s2, size_t n);

#endif