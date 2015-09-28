/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/28 16:27:32 by rbenjami          #+#    #+#             */
/*   Updated: 2014/06/22 20:58:13 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	LIBFT_H
# define LIBFT_H
# include <stdlib.h>
# include <unistd.h>

typedef enum	e_color
{
	RESET = 0,
	BLACK,
	RED,
	GREEN,
	YELLOW,
	BLUE,
	MAGENTA,
	CYAN,
	WHITE,
	B_BLACK,
	B_RED,
	B_GREEN,
	B_YELLOW,
	B_BLUE,
	B_MAGENTA,
	B_CYAN,
	B_WHITE
}				t_color;

typedef struct	s_pattern
{
	char		*str;
}				t_pattern;

/*
**	ANSI COLOR
*/
# define ANSI_COLOR_BLACK				("\x1b[30m")
# define ANSI_COLOR_RED					("\x1b[31m")
# define ANSI_COLOR_GREEN				("\x1b[32m")
# define ANSI_COLOR_YELLOW				("\x1b[33m")
# define ANSI_COLOR_BLUE				("\x1b[34m")
# define ANSI_COLOR_MAGENTA				("\x1b[35m")
# define ANSI_COLOR_CYAN				("\x1b[36m")
# define ANSI_COLOR_WHITE				("\x1b[36m")
# define ANSI_BACKGROUND_COLOR_BLACK	("\x1b[40m")
# define ANSI_BACKGROUND_COLOR_RED		("\x1b[41m")
# define ANSI_BACKGROUND_COLOR_GREEN	("\x1b[42m")
# define ANSI_BACKGROUND_COLOR_YELLOW	("\x1b[43m")
# define ANSI_BACKGROUND_COLOR_BLUE		("\x1b[44m")
# define ANSI_BACKGROUND_COLOR_MAGENTA	("\x1b[45m")
# define ANSI_BACKGROUND_COLOR_CYAN		("\x1b[46m")
# define ANSI_BACKGROUND_COLOR_WITHE	("\x1b[47m")
# define ANSI_COLOR_RESET				("\x1b[0m")

/*
**	BASE
*/
# define BINARY							(2)
# define TRINARY						(3)
# define OCTAL							(8)
# define NONAIRE						(9)
# define DECIMAL						(10)
# define HEXADECIMAL					(16)
# define SEXIGESIMAL					(60)

/*
**	ALIAS
*/
# define MIN(n, m)						((n) < (m) ? (n) : (m))
# define EQUAL(n, m)					(!ft_strcmp(n, m))

/*
**	PUT
*/
void			ft_putstr(char *str);
void			ft_putstr_fd(char *str, size_t fd);
void			ft_putendl(char *str);
void			ft_putendl_fd(char *str, size_t fd);
void			ft_putchar(char c);
void			ft_putchar_fd(char c, size_t fd);
void			ft_putmem(void *adr);
void			ft_putmem_fd(void *adr, size_t fd);
void			ft_putnbr_base(int n, size_t base);
void			ft_putnbr_base_fd(int n, size_t base, size_t fd);

/*
**	STR
*/
char			*ft_strchr(const char *s, int c);
char			*ft_strstr(const char *str, const char *find);
char			*ft_strncpy(char *dest, const char *src, size_t n);
size_t			ft_strlen(char *str);
int				ft_strcmp(char *str1, char *str2);
int				ft_strncmp(char *s1, char *s2, size_t n);
void			ft_colorize(t_color color, int backgroud);
char			*ft_strjoin_malloced(char *str1, char *str2);
char			*ft_strjoin(char *str1, char *str2);
char			*ft_strdup(char *str);
char			*ft_strsub(char const *s, size_t start, size_t len);
char			**ft_strsplit(char const *s, char c);
char			*ft_trunc(const char *msg, ...);
t_pattern		pattern(int repeat, const char *msg, ...);

/*
**	TAB
*/
size_t			ft_tabsize(void **tab);
void			ft_freetab(void **tab);
char			**ft_cpytab(char **tab, int lenth);
int				**ft_cpytab_int(int **tab, int x, int y);

/*
**	IS
*/
int				ft_isalnum(int c);
int				ft_islower(int c);
int				ft_isupper(int c);
int				ft_isalpha(int c);
int				ft_isascii(int c);
int				ft_isdigit(int c);
int				ft_isprint(int c);
int				ft_isspace(char c);

/*
**	CONVERT
*/
char			*ft_itoa(int n);
int				ft_atoi(const char *str);

/*
**	MEM
*/
void			*ft_memalloc(size_t size);
void			*ft_memrealloc(void **ptr, size_t size, size_t new_size);
char			*ft_strnew(size_t size);
void			ft_bzero(void *s, size_t n);
void			*ft_memcpy(void *dest, const void *src, size_t n);
void			ft_memdel(void **mem);

/*
**	ERROR
*/
int				error(const char *msg, ...);
void			exit_error(char *error);

/*
**	UTILS
*/
int				get_next_line(int fd, char **line);
void			add_char(char **res, char c);
void			add_str(char **res, char *str);
void			add_int(char **res, int i);
void			add_pattern(char **res, t_pattern pat);

#endif
