/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnegro <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 15:51:10 by mnegro            #+#    #+#             */
/*   Updated: 2023/07/20 17:48:54 by mnegro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* HEADER FILES */
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>

/* MACROS */

/* STRUCTURES */
typedef struct s_mini
{
	char	*input;
}			t_mini;

/* PROTOTYPES */
/* main.c */

/* parseInput.c */
// void	ft_parse_input(char *input);
// void	**ft_split_toby(char *input, char c);
// void	**ft_split_red(char *input, char c);
// void	**ft_split(char *input, char c);
/* parseUtils.c */
int		ft_get_wc(char *str);
void	ft_handle_quotes(char *str, int *flag, int *i);

#endif
