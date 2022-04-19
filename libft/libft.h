/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okinnune <okinnune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 17:57:33 by okinnune          #+#    #+#             */
/*   Updated: 2022/04/19 17:24:08 by okinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include "get_next_line.h"

/* memory	*/
void			*ft_memset(void *ptr, int value, size_t num);
void			*ft_memcpy(void *dst, const void *src,
					size_t n);
void			*ft_memccpy(void *dst, const void *src,
					int c, size_t n);
void			*ft_memmove(void *dst, const void *src, size_t len);
char			*ft_memdup(const void *m, size_t n);
int				ft_memcmp(const void *ptr1, const void*ptr2, size_t num);
void			ft_memdel(void **ap);
void			*ft_memalloc(size_t size);
void			*ft_memchr(const void *ptr, int c, size_t n);
void			ft_bzero(void *s, size_t n);

/* strings	*/
size_t			ft_strlcat(char *dst, const char *src, size_t siz);
size_t			ft_strlen(const char *str);
char			*ft_strchr(const char *str, int character);
char			*ft_strrchr(const char *str, int character);
char			*ft_strstr(const char *haystack, const char *needle);
char			*ft_strnstr(const char *haystack, const char *needle,
					size_t len);
char			*ft_strdup(const char *str);
int				ft_strcmp(const char *s1, const char *s2);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
char			*ft_strcat(char *destination, const char *source);
char			*ft_strncat(char *s1, const char *s2, size_t n);
char			*ft_strcpy(char *dest, const char *src);
void			ft_strdel(char **as);
char			*ft_strnew(size_t size);
void			ft_strclr(char *s);
void			ft_strfill(char *s, char c); /*extra*/
char			**ft_strsplit(const char *s, char c);
char			**ft_strscrape(const char*s, char *delims);
char			*ft_strncpy(char *dest, const char *src, size_t num);
void			ft_striter(char *s, void (*f)(char *));
void			ft_striteri(char *s, void (*f)(unsigned int, char *));
int				ft_strequ(const char *s1, const char *s2);
int				ft_strnequ(const char *s1, const char *s2, size_t n);
char			*ft_strmap(const char *s, char (*f)(char));
char			*ft_strmapi(const char *s, char (*f)(unsigned int, char));
char			*ft_strtrim(const char *s);
char			*ft_strsub(const char *s, unsigned int start, size_t len);
char			*ft_strjoin(const char *s1, const char *s2);
int				ft_isdigit(int c);
char			*ft_itoa(int n);
char			*ft_ftoa(float f, int dec);
int				ft_isprint(int c);
int				ft_isspace(int c);
int				ft_isalpha(int c);
int				ft_atoi(const char *str);
int				ft_tolower(int c);
int				ft_toupper(int c);
int				ft_isalnum(int c);
int				ft_isascii(int c);
void			ft_putstr(const char *s);
void			ft_putstr_fd(const char *s, int fd);
void			ft_putendl(const char *s);
void			ft_putendl_fd(const char *s, int fd);
void			ft_putchar(char c);
void			ft_putchar_fd(char s, int fd);
void			ft_putnbr(int i);
void			ft_putnbr_fd(int n, int fd);

/* "math" */
int				ft_digitcount(int n);/*extra*/
int				ft_pow(int n, int p);/*extra*/
int				ft_abs(int n);/*extra*/
int				ft_sqrt(int nb);/*extra*/
int				ft_clamp(int val, int min, int max);
int				ft_min(int i1, int i2);
int				ft_max(int i1, int i2);
float			ft_clampf(float val, float min, float max);

/* lists */
typedef struct s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}	t_list;

t_list			*ft_lstnew(const void *content, size_t content_size);
t_list			*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
void			ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void			ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void			ft_lstiter(t_list *lst, void (*f)(t_list *elem));
void			ft_lstadd(t_list **alst, t_list *new);
void			ft_lstapp(t_list **alst, t_list *new);/*extra*/

#endif