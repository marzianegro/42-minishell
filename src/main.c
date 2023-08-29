/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnegro <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 15:51:17 by mnegro            #+#    #+#             */
/*   Updated: 2023/08/29 18:51:20 by mnegro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_parse_line(t_mini *shell)
{
	int		i;
	char	**toby;
	char	**red;

	i = 0;
	while (shell->line && shell->line[i])
	{
		if (shell->line[i] == '|')
			i++;
		toby = ft_split_toby(shell->line, i);
		red = ft_split_red(shell->line, &i);
		ft_frontnew_tkn(&(shell->tkn), toby, red);
	}
	ft_parse_token(&shell->tkn, shell);
}

int	main(int argc, char **argv, char **envp)
{
	t_mini		shell;

	(void)argv;
	if (argc != 1)
	{
		ft_putstr_fd("\033[1;91mError\033[0;39m: invalid input!\n", 2);
		return (1);
	}
	ft_init_shell(&shell, envp);
	while (1)
	{
		ft_check_signal();
		shell.line = readline("minishell-$ ");
		if (shell.line[0] != '\0')
		{
			ft_putstr_fd_ms(shell.line, shell.history_fd);
			add_history(shell.line);
			ft_parse_line(&shell);
			shell.exit_code = ft_whether_pipe(&shell); // aggiungere controllo? why not
		}
		ft_clear_tkn(&shell.tkn);
		free(shell.line);
	}
	return (0);
}
