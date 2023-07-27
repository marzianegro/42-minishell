/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnegro <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 15:51:10 by mnegro            #+#    #+#             */
/*   Updated: 2023/07/27 18:50:34 by mnegro           ###   ########.fr       */
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

typedef struct s_mtx
{
	char	**toby;
	char	**red;
}			t_mtx;

typedef struct s_rt
{
}			t_rt;

typedef struct s_mini
{
	char	*line;
	char	*history;
}			t_mini;

/* PROTOTYPES */
/* history.c */
void	ft_init_history(t_mini *shell);
/* main.c */
/* parsing.c */
void	ft_parse_line(char *line);
/* split_red.c */
char	**ft_split_red(char *line);
/* split_toby.c */
char	**ft_split_toby(char *line);
/* utils.c */
void	ft_check_quotes(char *str, char c, int *len);
void	ft_check_redirects(char *str, int *i);
int		ft_is_stop(char c, int n);
void	ft_print_mtx(char **mtx);
int		ft_whether_quotes(t_split *data);

#endif
