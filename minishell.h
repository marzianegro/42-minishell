/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnegro <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 15:51:10 by mnegro            #+#    #+#             */
/*   Updated: 2023/08/21 17:42:21 by mnegro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* HEADER FILES */
# include <fcntl.h>
# include "libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <sys/wait.h>
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

typedef struct s_token
{
	char			**toby;
	char			**red;
	struct s_token	*next;
}			t_token;

typedef struct s_parse
{
	int		x;
	int		y;
	int		len;
	char	*new;
	char	*key;
}			t_parse;

typedef struct s_env
{
	char			*key;
	char			*value;
	char			*vbl;
	struct s_env	*next;
}			t_env;

typedef struct s_variable
{
	char				*key;
	char				*value;
	struct s_variable	*next;
}			t_variable;	

typedef struct s_mini
{
	char		*line;
	const char	*history;
	int			history_fd;
	t_token		*tkn;
	t_env		*envp;
	t_variable	*vbl;
	int			std_in;
	int			std_out;
	int			exit_code;
	int			exit_status;
}			t_mini;


/* PROTOTYPES */
/* built_ins.c */
void	ft_cd(t_mini *shell, char **mtx);
void	ft_history(t_mini *shell);
void	ft_echo(char **mtx);
void	ft_unset(t_mini *shell, char **mtx);
void	ft_pwd(t_mini *shell);
/* built_ins2.c */
void	ft_clear(t_mini *shell, char **mtx);
void	ft_export(t_mini *shell);
void	ft_env(t_mini *shell);
void	ft_exit(t_mini *shell, char **mtx);
void	ft_vbl(t_mini *shell, char *cmd);
/* builtins_utils.c */
int		ft_check_vbl(char *str);
char	*ft_key(char *str);
char	*ft_value(char *str);
void	ft_set_exp(t_mini *shell);
void	ft_backnew_vbl(t_variable **vbl, char *key, char *value);
/* exec_multi.c */
int		ft_exec_pipe(t_mini *shell, t_token *tkn);
int		ft_mini_pipe(t_mini *shell, t_token *tkn);
/* exec_red.c */
int		ft_exec_red(t_mini *shell, char **mtx);
/* exec_toby.c */
int		ft_exec_toby(t_mini *shell, char **mtx);
void	ft_exec_binary(t_mini *shell, t_token *tkn);
/* exec.c */
int		ft_whether_pipe(t_mini *shell);
/* init_shell.c */
void	ft_init_history(t_mini *shell);
t_env	*ft_init_env(char **mtx);
void	ft_init_shell(t_mini *shell, char **envp);
/* init_utils.c */
void	ft_backnew_env(t_env **envp, char *key, char *value);
void	ft_set_env(char **mtx, int y, t_env **envp);
/* main.c */
void	ft_parse_line(t_mini *shell);
/* prs_utils.c */
void	ft_new_str(char *str, t_parse *prs);
int		ft_stoppers(char c);
int		ft_handle_stoppers(char **mtx, t_mini *shell, t_parse *prs);
void	ft_single_quotes(char **mtx, t_parse *prs);
int		ft_double_quotes(char **mtx, t_mini *shell, t_parse *prs);
/* prs_utils2.c */
int		ft_variables(char **mtx, t_mini *shell, t_parse *prs);
int		ft_regular_vbl(char **mtx, t_mini *shell, t_parse *prs);
/* prs.c */
void	ft_parse_token(t_token **tk, t_mini *shell);
void	ft_parser(char **mtx, t_mini *shell);
int		ft_parser_red(char **mtx, t_parse *prs);
/* spl_red.c */
char	**ft_split_red(char *line, int *i);
/* spl_toby.c */
char	**ft_split_toby(char *line, int i);
/* spl_utils.c */
void	ft_check_quotes(char *str, char c, int *len);
void	ft_check_redirects(char *str, int *i);
int		ft_is_stop(char c, int n);
int		ft_whether_quotes(t_split *spl);
void	ft_regular_red(char *line, t_split *spl);
/* tkn_utils.c */
void	ft_addfront_new(t_token **tkn, char **toby, char **red);
void	ft_clear_token(t_token **tkn);
void	ft_iter(t_token *tkn, t_mini *shell, void (*f)(char **, t_mini *));
void	ft_print_token(t_token *tkn);
/* utils.c */
void	ft_freematrix(char **matrix);
void	ft_print_mtx(char **mtx);
void	ft_putstr_fd_ms(char *s, int fd);
/* vbl_utils.c */
int		ft_is_key(char c, int n);
void	ft_new_key(char *str, char **new, int start, int len);
void	ft_fix_key(char *str, t_parse *prs);
t_env	*ft_get_key(t_env *envp, t_parse *prs);
void	ft_expand(t_env *envp, t_parse *prs);
#endif
