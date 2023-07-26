/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnegro <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 15:51:10 by mnegro            #+#    #+#             */
/*   Updated: 2023/07/26 16:07:04 by mnegro           ###   ########.fr       */
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
	int	redirect;
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
	char	*input;
	char	*history;
}			t_mini;

/* PROTOTYPES */
/* history.c */
/* main.c */
/* split_all.c */
/* split_red.c */
/* split_toby.c */
void	ft_handle_quotes(char *line, t_split *data);
int		ft_word_count(char *line);
char	**ft_split_toby(char *line);
/* utils.c */
int		ft_is_stop(int c, int n);

#endif
