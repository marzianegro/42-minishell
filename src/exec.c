/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnegro <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 16:09:33 by mnegro            #+#    #+#             */
/*   Updated: 2023/08/29 18:51:19 by mnegro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_save_exit(t_mini *shell, int code)
{
	static t_mini	*tmp;

	if (shell)
		tmp = shell;
	else
		tmp->exit_code = code;
}

void	ft_check_signal(void)
{
	signal(SIGINT, ft_signal_handler);
	// signal(CTRL-D ft_signal_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	ft_signal_handler(int signal)
{
	if (signal == SIGINT)
	{
		// ft_save_exit(NULL, 130);
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

int	ft_whether_pipe(t_mini *shell)
{
	if (shell->tkn && !shell->tkn->next)
	{
		shell->exit_status = ft_exec_red(shell, shell->tkn);
		if (shell->exit_status)
			return (shell->exit_status);
		ft_dup(shell, -1, -1);
		shell->exit_status = ft_exec_toby(shell, shell->tkn->toby);
		return (shell->exit_status);
	}
	else
		return (ft_mini_pipe(shell, shell->tkn));
	return (0);
}
