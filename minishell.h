/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnegro <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 15:51:10 by mnegro            #+#    #+#             */
/*   Updated: 2023/08/16 15:48:40 by mnegro           ###   ########.fr       */
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

typedef struct s_parse
{
	int		sq;
	int		dq;
	int		len;
	char	*new;
	char	*key;
}			t_parse;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}			t_env;

typedef struct s_mini
{
	char		*line;
	const char	*history;
	int			history_fd;
	t_rt		*parsley;
	t_env		*envp;
}			t_mini;


/* PROTOTYPES */
/* init_shell.c */
void	ft_init_history(t_mini *shell);
void	ft_init_env(char **mtx);
void	ft_init_shell(t_mini *shell, char **envp);
/* init_utils.c */
void	ft_addback_new(t_env **envp, char *key, char *value);
void	ft_set_env(char **mtx, int y, t_env **envp);
/* main.c */
void	ft_parse_line(t_mini *shell);
/* parser_utils.c */
int		ft_stoppers(char *str, int i);
void	ft_handle_stoppers(char **mtx, int x, int y, t_parse *prs);
void	ft_single_quotes(char **mtx, int x, int y, t_parse *prs);
void	ft_double_quotes(char **mtx, int x, int y, t_parse *prs);
void	ft_variables(char **mtx, int x, int y, t_parse *prs);
/* parser.c */
void	ft_parse_rt(t_rt **rt);
void	ft_new_str(char *str, char **new, int start, int len);
void	ft_parser(char **mtx, t_mini *shell);
/* parse_utils.c */
void	ft_new_str(char *str, char **new, int start, int len);
/* rt_utils.c */
void	ft_addfront_new(t_rt **rt, char **toby, char **red);
void	ft_clear(t_rt **rt);
void	ft_iter(t_rt *rt, void (*f)(char **));
void	ft_print_rt(t_rt *rt);
/* split_red.c */
char	**ft_split_red(char *line, int *i);
/* split_toby.c */
char	**ft_split_toby(char *line, int i);
/* split_utils.c */
void	ft_check_quotes(char *str, char c, int *len);
void	ft_check_redirects(char *str, int *i);
int		ft_is_stop(char c, int n);
int		ft_whether_quotes(t_split *spl);
/* utils.c */
void	ft_freematrix(char **matrix);
void	ft_print_mtx(char **mtx);
void	ft_putstr_fd_ms(char *s, int fd);

#endif
