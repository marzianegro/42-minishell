/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_multi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnegro <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 11:08:37 by mnegro            #+#    #+#             */
/*   Updated: 2023/08/21 17:40:47 by mnegro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//	DA RICONTROLARE TUTTO - NON TESTATO
int	ft_exec_pipe(t_mini *shell, t_token *tkn)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (!pid)
	{
		shell->exit_status = ft_exec_red(shell, tkn->red);
		if (!shell->exit_status)
		{
			ft_exec_toby(shell, shell->tkn->toby);
			shell->exit_status = ft_whether_pipe(shell);
		}
		free(shell); // forse è necessaria un afunzione di free della shell
		exit(shell->exit_status);
	}
	wait(&status);
	shell->exit_status = WEXITSTATUS(status);
	return (shell->exit_status);
}

/* In questa funzione ft_exec_red() viene chiamata ricorsivamente usando pipe()
e con tkn->next come parametro */
int	ft_mini_pipe(t_mini *shell, t_token *tkn)
{
	int	p[2];

	if (tkn->next)
	{
		pipe(p);
		ft_mini_pipe(shell, tkn->next);
	}
	else
	{
		p[0] = -1;
		p[1] = shell->std_in;
	}
	if (p[1] < 0)
		close(p[1]);
	return (ft_exec_pipe(shell, tkn));
}
