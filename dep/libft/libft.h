/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-clee <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 14:47:20 by mde-clee          #+#    #+#             */
/*   Updated: 2023/09/16 09:24:46 by mde-clee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <stdio.h>

# ifndef OPEN_MAX
#  define OPEN_MAX FOPEN_MAX
# endif

# ifdef BUFFER_SIZE
#  if BUFFER_SIZE < 1
#   undef BUFFER_SIZE
#  endif
#  if BUFFER_SIZE > 1000000
#   undef BUFFER_SIZE
#  endif
# endif

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 128
# endif

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

int			ft_atoi(const char *str);
void		ft_bzero(void *s, size_t n);
void		*ft_calloc(size_t count, size_t size);
int			ft_isalnum(int c);
int			ft_isalpha(int c);
int			ft_isascii(int c);
int			ft_isdigit(int c);
int			ft_isprint(int c);
char		*ft_itoa(int n);
void		*ft_memchr(const void *s, int c, size_t n);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
void		*ft_memcpy(void *dst, const void *src, size_t n);
void		*ft_memmove(void *dst, const void *src, size_t n);
void		*ft_memset(void *b, int c, size_t len);
char		*ft_pstrdup(const char *s);
void		ft_putchar_fd(char c, int fd);
void		ft_putendl_fd(char *s, int fd);
void		ft_putnbr_fd(int n, int fd);
void		ft_putstr_fd(char *s, int fd);
char		**ft_split(char const *s, char c);
char		*ft_strcchr(char *str, char c, size_t n);
char		*ft_strchr(const char *s, int c);
void		ft_strcncpy(char *dest, char *src, size_t n);
char		*ft_strdup(const char *s1);
void		ft_striteri(char *s, void (*f)(unsigned int, char *));
char		*ft_strjoin(char const *s1, char const *s2);
size_t		ft_strlcat(char *dst, const char *src, size_t dstsize);
size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t		ft_strlen(const char *s);
int			ft_strracat(char **dest, char *src);
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*ft_strnstr(const char *haystack, const char *needle, size_t len);
char		*ft_strrchr(const char *s, int c);
char		*ft_strtrim(char const *s1, char const *set);
char		*ft_substr(char const *s, unsigned int start, size_t len);
int			ft_tolower(int c);
int			ft_toupper(int c);
void		ft_lstadd_back(t_list **lst, t_list *new);
void		ft_lstadd_front(t_list **lst, t_list *new);
void		ft_lstclear(t_list **lst, void (*del)(void *));
void		ft_lstdelone(t_list *lst, void (*del)(void *));
void		ft_lstiter(t_list *lst, void (*f)(void *));
t_list		*ft_lstlast(t_list *lst);
t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
t_list		*ft_lstnew(void *content);
int			ft_lstsize(t_list *lst);
char		**ft_csplit(const char *s, size_t *arr);
long long	ft_atoll(const char *s);
int			ft_isllong(char *s);
int			ft_pputchar_fd(char c, int fd);
int			ft_pputstr_fd(char *s, int fd);
char		*ft_pstrdup(const char *s);
int			ft_putnbr_base_fd(long n, int base, int fd);
void		ft_sort_strstr_tab(char ***tab, int size, int mode);
wchar_t		*ft_stowcdup(const char *src);
wchar_t		*ft_stowcedup(const char *src, int *error);
wchar_t		*ft_stowcndup(const char *src, size_t n);
int			ft_strcasecmp(const char *s1, const char *s2);
int			ft_strcmp(const char *s1, const char *s2);
char		*ft_strdupchr(const char *src, char c);
char		*ft_strduprchr(const char *src, char c);
char		*ft_strduprnchr(const char *src, char c, size_t n);
char		*ft_strfjoin(char *s1, const char *s2);
char		**ft_strstrdup(const char **src);
size_t		ft_strstrlen(const char **src);
int			ft_wcscmp(const wchar_t *s1, const wchar_t *s2);
wchar_t		*ft_wcsdup(const wchar_t *src);
size_t		ft_wcslen(const wchar_t *s);
wchar_t		*ft_wcsndup(const wchar_t *src, size_t n);
int			ft_isnumeric(char *s);
int			ft_isspace(char c);
int			ft_altoi(char **str, int *nbr);
int			ft_merge_sort(int *arr, int size);
int			ft_min(int a, int b);
int			ft_max(int a, int b);
int			ft_abs(int a);
char		*get_next_line(int fd);
void		skip_spaces(char **s);

#endif
