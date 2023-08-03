/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnegro <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 15:51:10 by mnegro            #+#    #+#             */
/*   Updated: 2023/08/03 16:24:50 by mnegro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* HEADER FILES */
# include <fcntl.h>
# include "libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

/* MACROS */

/* STRUCTURES */

typedef struct s_split
{
	int	i;
	int	sq;
	int	dq;
	int	words;
}			t_split;

typedef struct s_rt
{
	char		**toby;
	char		**red;
	struct s_rt	*next;
}			t_rt;

typedef struct s_mini
{
	char		*line;
	const char	*history;
	int			history_fd;
	t_rt		*parsley;
}			t_mini;

/* PROTOTYPES */
/* history.c */
void	ft_init_history(t_mini *shell);
/* init_shell.c */
void	ft_init_shell(t_mini *shell);
/* main.c */
/* parsing.c */
void	ft_parse_line(t_mini *shell);
/* rt_utils.c */
void	ft_addfront_new(t_rt **rt, char **toby, char **red);
void	ft_freematrix(char **matrix);
void	ft_clear(t_rt **rt);
void	ft_print_mtx(char **mtx);
void	ft_print_rt(t_rt *rt);
/* split_red.c */
char	**ft_split_red(char *line, int *i);
/* split_toby.c */
char	**ft_split_toby(char *line, int i);
/* utils.c */
void	ft_check_quotes(char *str, char c, int *len);
void	ft_check_redirects(char *str, int *i);
int		ft_is_stop(char c, int n);
int		ft_whether_quotes(t_split *data);
void	ft_putstr_fd_ms(char *s, int fd);

#endif
