/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnegro <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 16:09:33 by mnegro            #+#    #+#             */
/*   Updated: 2023/08/21 18:32:56 by mnegro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_get_token(t_mini *shell, t_token *tkn)
{
	char	*path;
	
}

void ft_check_signal(t_mini *shell, int signal, int exit_code)
{
	t_mini	*sign;

	if (signal == SIGINT)
	{
		if (shell)
			sign = shell;
		else
			sign->exit_code = exit_code;
			shell = NULL;
			write (1, "\n", 1);	
	}
}

int	ft_whether_pipe(t_mini *shell)
{
	signal(SIGINT, ft_check_signal); //controlla segnale interrotto Ctrl+C
	if (shell->tkn && !shell->tkn->next)
	{
		shell->exit_status = ft_exec_red(shell, shell->tkn->red);
		if (shell->exit_status)
			return (shell->exit_status);
		ft_dup(shell, -1, -1);
		shell->exit_status = ft_exec_toby(shell, shell->tkn->toby);
		return (shell->exit_status);
	}
	else
		return (ft_mini_pipe(shell, shell->tkn));
}
