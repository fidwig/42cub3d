/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsommet <jsommet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 15:22:56 by jsommet           #+#    #+#             */
/*   Updated: 2024/11/18 18:18:31 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include "garbage_collector.h"

int				ft_isalpha(int c);
int				ft_isdigit(int c);
int				ft_isalnum(int c);
int				ft_isascii(int c);
int				ft_isprint(int c);
size_t			ft_strlen(const char *s);
void			*ft_memset(void *s, int c, size_t n);
void			*ft_bzero(void *s, size_t n);
void			*ft_memcpy(void *dest, const void *src, size_t n);
void			*ft_memmove(void *dest, const void *src, size_t n); //
size_t			ft_strlcpy(char *dst, const char *src, size_t size);
size_t			ft_strlcat(char *dst, const char *src, size_t size); //
int				ft_toupper(int c);
int				ft_tolower(int c);
char			*ft_strchr(const char *s, int c);
char			*ft_strrchr(const char *s, int c);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
void			*ft_memchr(const void *s, int c, size_t n);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
char			*ft_strnstr(const char *big, const char *little, size_t len);
int				ft_atoi(const char *nptr);
void			*ft_calloc(size_t nmemb, size_t size); //
void			*gc_calloc(size_t nmemb, size_t size);
char			*ft_strdup(const char *s);
char			*gc_strdup(const char *s);
char			*ft_substr(char const *s, unsigned int start, size_t len);
char			*gc_substr(char const *s, unsigned int start, size_t len);
char			*ft_strjoin(char const *s1, char const *s2);
char			*gc_strjoin(char const *s1, char const *s2);
char			*ft_strtrim(char const *s1, char const *set);
char			*gc_strtrim(char const *s1, char const *set);
char			**ft_split(char const *s, char c);
char			**gc_split(char const *s, char c);
char			*ft_itoa(int n);
char			*gc_itoa(int n);
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void			ft_striteri(char *s, void (*f)(unsigned int, char*));
void			ft_putchar_fd(char c, int fd);
void			ft_putstr_fd(char *s, int fd);
void			ft_putendl_fd(char *s, int fd);
void			ft_putnbr_fd(int n, int fd);

// late additions
char			**ft_splitf(char const *s, int (*f)(int));
char			*ft_strcpy(char *dst, const char *src);
char			*ft_strdup_free(const char *s, int free_s);
char			*gc_strdup_free(const char *s, int free_s);
char			*ft_strjoin_free(char const *s1, char const *s2, int free1,
					int free2);
char			*gc_strjoin_free(char const *s1, char const *s2, int free1,
					int free2);
char			*ft_strndup(const char *s, size_t len);
int				ft_dprintf(int fd, const char *format, ...);
int				ft_isspace(int c);
int				*ft_max_arr(int *arr, size_t len);
int				ft_max(int a, int b);
int				*ft_min_arr(int *arr, size_t len);
int				ft_min(int a, int b);
int				ft_strcmp(const char *s1, const char *s2);
long			ft_atol(const char *nptr);
size_t			ft_splitlen(char **arr);
unsigned int	count_wordsf(char const *s, int (*f)(int));
unsigned int	ft_abs(int n);
unsigned int	ft_atou_base(const char *nptr, const char *base);

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

t_list			*ft_lstnew(void *content);
t_list			*gc_lstnew(void *content);
void			*ft_lstadd_front(t_list **lst, t_list *new);
int				ft_lstsize(t_list *lst);
t_list			*ft_lstlast(t_list *lst);
void			*ft_lstadd_back(t_list **lst, t_list *new);
void			ft_lstdelone(t_list *lst, void (*del)(void*));
void			gc_lstdelone(t_list *lst, void (*del)(void*));
void			ft_lstclear(t_list **lst, void (*del)(void *));
void			gc_lstclear(t_list **lst, void (*del)(void *));
void			ft_lstiter(t_list *lst, void (*f)(void *));
t_list			*ft_lstmap(t_list *lst, void *(*f)(void *),
					void (*del)(void *));
t_list			*gc_lstmap(t_list *lst, void *(*f)(void *),
					void (*del)(void *));

// late additions
void			ft_lstremove(t_list **lst, t_list *link, void (*del)(void *));
void			gc_lstremove(t_list **lst, t_list *link, void (*del)(void *));
void			ft_lstunlink(t_list **lst, t_list *link);

#endif
