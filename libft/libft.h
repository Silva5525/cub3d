/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdegraf <wdegraf@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 14:13:48 by wdegraf           #+#    #+#             */
/*   Updated: 2025/02/23 15:21:33 by wdegraf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <string.h>
# include <stdlib.h>
# include <stdarg.h>
# include <unistd.h>
# include <stdint.h>
# include <math.h>
# include <stdio.h>
# include <stdbool.h>
# include "get_next_line.h"

/// @brief coordinations struct for ft_fill.c 
typedef struct s_xy
{
	int		x;
	int		y;
}			t_xy;

/// @brief linked list struct for all ft_lst*.c
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

int		ft_atoi(const char *str);
int		ft_isalnum(char c);
int		ft_isalpha(int a);
int		ft_isascii(int a);
int		ft_isdigit(char d);
int		ft_isprint(int a);
int		ft_isspace(int c);
int		ft_tolower(int c);
int		ft_toupper(int c);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strncpy(char *dst, const char *src, size_t n);
size_t	ft_strnlen(const char *str, size_t n);
char	*ft_strndup(const char *src, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
void	ft_bzero(void *s, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dst, const void *src, size_t len);
void	*ft_memset(void *str, int value, size_t len);
void	*ft_calloc(size_t count, size_t size);
void	*ft_realloc(void *ptr, size_t old_size, size_t new_size);
size_t	ft_strlen(const char *str);
char	*ft_strcpy(char *dst, const char *src);
size_t	ft_strlcpy(char *dst, const char *src, size_t ds);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	*ft_strdup(const char *s1);
char	**ft_strdup_double(char **str);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_itoa(int n);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

char	**ft_split(const char *s, char c);
void	f_it(char **out1);

int		ft_printf(const char *format, ...);
int		v_x(va_list *args, const char *base_char, ssize_t *wr_i);
int		v_p_else( ssize_t *wr_i, char *hex, int i);
int		v_p(va_list *args, const char *base_char, ssize_t *wr_i);
int		v_u(va_list *args, ssize_t *wr_i);
int		v_di(va_list *args);

int		ft_intlen(int n);
void	ft_lstiter_ptr(t_list *lst, void (*f)(void *, void *), void *ptr);
t_list	*ft_lstget(t_list *lst, int index);
ssize_t	ft_strcwords(char *str, char delimeter);
ssize_t	ft_strcwords_isspace(char *str);
ssize_t	ft_ato_ssize_t(const char *str);
bool	ft_fill(char **tab, t_xy size, t_xy begin);
int		ft_unsetenv(const char *name, char **envp);
int		ft_setenv(const char *str, const char *v, char **envp);
ssize_t	ft_write(int fd, const void *buf, size_t count);
char	*ft_strtok_thread(char *str, const char *delim, char **saveptr);
char	*ft_strtok(char *str, const char *delim);
char	*ft_strstr(const char *haystack, const char *needle);
char	*ft_strcat(char *dst, const char *src);
char	*ft_strjoin_multiple(char *hold, char *next);
char	*ft_build_f_path(char *path, char *name);
int		ft_isupper(int c);
bool	ft_isnumeric(const char *str);
void	ft_write_smite(void);
double	ft_magnitude(double re, double im);
bool	ft_str_end_with(const char *str, const char *end);
bool	ft_check_wall(size_t map_width, size_t map_height, char **map);
size_t	ft_strspn(const char *s, const char *accept);
bool	ft_access_read_write(const char *path, int mode);

#endif
