/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsodre-p <tsodre-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 11:20:25 by tsodre-p          #+#    #+#             */
/*   Updated: 2025/01/03 09:54:52 by tsodre-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdarg.h>
# include <stdbool.h>

/*-----------------------CONVERSIONS-----------------------*/

int			ft_atoi(const char *str);
long		ft_atol(const char *str);
long long	ft_atoll(const char *str);
char		*ft_itoa(int n);
int			ft_abs(int n);
int			ft_tolower(int c);
int			ft_toupper(int c);
char		*ft_utoa(unsigned long long n);

/*-------------------------NUMBERS-------------------------*/

int			ft_nbrlen(long long nbr);

/*---------------------------MEM---------------------------*/

void		*ft_memchr(const void *str, int c, size_t n);
int			ft_memcmp(char *s1, char *s2, size_t n);
void		*ft_memcpy(void *dest, const void *src, size_t n);
void		*ft_memmove(void *dest, const void *src, size_t n);
void		*ft_memset(void *str, int c, size_t n);
void		ft_bzero(void *str, size_t n);
void		*ft_calloc(size_t nmemb, size_t size);

/*--------------------------CHECK--------------------------*/

int			ft_isalnum(int c);
int			ft_isalpha(int c);
int			ft_isascii(int c);
int			ft_isdigit(int c);
int			ft_isprint(int c);
int			ft_isspace(int c);
int			ft_isnumeric(const char *str);
int			ft_getlength(unsigned long long n, int base);

/*-------------------------STRINGS-------------------------*/

char		**ft_split(char const *s, char c);
void		ft_free_split(char **split);
char		*ft_strchr(const char *str, int c);
char		*ft_strdup(const char *str);
void		ft_striteri(char *s, void (*f)(unsigned int, char*));
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strcjoin(char const *s1, char c);
size_t		ft_strlcat(char *dest, const char *src, size_t size);
size_t		ft_strlcpy(char *dest, const char *src, size_t size);
size_t		ft_strlen(const char *str);
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int			ft_strcmp(char *s1, char *s2);
int			ft_chrcmp(char first, char second);
int			ft_strncmp(char *s1, char *s2, size_t n);
char		*ft_strnstr(const char *big, const char *little, size_t n);
char		*ft_strrchr(const char *str, int c);
char		*ft_strtrim(char const *str, char const *set);
char		*ft_substr(char const *str, unsigned int start, size_t len);
int			ft_wordcount(const char *str, char c);
void		ft_swap(char **s1, char **s2);
int			ft_isquote(int c);

/*---------------------------ARRAY OF STRINGS---------------------------*/
int			ft_dpcount(char **dp);
char		**ft_dpdup(char **dp, int size);

/*---------------------------PUT---------------------------*/

void		ft_putchar_fd(char c, int fd);
void		ft_putendl_fd(char *str, int fd);
void		ft_putnbr_fd(int nb, int fd);
void		ft_putstr_fd(char *str, int fd);

/*--------------------------LISTS--------------------------*/

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}				t_list;

void		ft_lstadd_back(t_list **lst, t_list *new);
void		ft_lstadd_front(t_list **lst, t_list *new);
void		ft_lstclear(t_list **lst, void (*del)(void *));
void		ft_lstdelone(t_list *lst, void (*del)(void *));
void		ft_lstiter(t_list *lst, void (*f)(void *));
t_list		*ft_lstlast(t_list *lst);
t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
t_list		*ft_lstnew(void *content);
int			ft_lstsize(t_list *lst);

/*---------------------------GET---------------------------*/

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char		*get_next_line_multifd(int fd);
char		*get_next_line(int fd);

/*------------------------FT_PRINTF------------------------*/

typedef struct s_format
{
	char	conversion_type;
	bool	space;
	bool	zero;
	bool	plus;
	bool	minus;
	bool	hash;
	bool	point;
	int		width;
	int		precision;
}	t_buffer;

# define TYPE "%cspdiuxX"
# define FLAGS "0 +-.#"

int			ft_printf(const char *str, ...);
int			ft_putchar(char c);
int			ft_putnbr(long long nb);
int			ft_puthexa(unsigned long nb, char c);
int			ft_putaddress(unsigned long nb);
int			ft_putstr(char *str);
int			ft_putunsignednbr(unsigned int nb);
int			ft_format_putchar(t_buffer *values, char c);
int			ft_format_puthexa(t_buffer *values, unsigned long long nb);
int			ft_phexa01(char *hexastr, t_buffer *values, int len, char base);
int			ft_phexaw1(char *hexastr, t_buffer *values, int len, char base);
int			ft_phexamw1(char *hexastr, t_buffer *values, int len);
int			ft_format_putstr(t_buffer *values, char *str);
int			ft_format_putaddress(t_buffer *values, unsigned long nb);
int			ft_paddmw1(char *hexastr, t_buffer *values, int precision, int len);
int			ft_paddw1(char *hexastr, t_buffer *values, int precision, int len);
int			ft_paddw2(char *hexastr, t_buffer *values, int len);
int			ft_paddz1(char *hexastr, t_buffer *values, int precision, int len);
int			ft_paddz2(char *hexastr, t_buffer *values, int len);
int			ft_format_putnbr(t_buffer *values, long long nb);
int			ft_format_putposnbr(t_buffer *values, unsigned long long nb);
int			ft_print_posnbrw2(char *number, t_buffer *values, int len);
int			ft_format_putunsignnbr(t_buffer *values, unsigned long long nb);
char		*ft_get_hexastr(unsigned long long nb, char *base);
int			ft_get_format_buffer(const char **str, va_list args);
int			ft_check_type_format(va_list args, t_buffer *values);

#endif
