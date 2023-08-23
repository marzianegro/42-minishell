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
	int		pipe;
	int		status;

	pid = fork();
	if (!pid)
	{
		pipe = ft_exec_red(shell, tkn);
		if (!pipe)
		{
			ft_dup(shell, oldfd, newfd);
			pipe = ft_exec_toby(shell, tkn->toby);
			
		}
		free(shell); // forse è necessaria un afunzione di free della shell
		exit(shell->exit_status);
	}
	wait(&status);
	shell->exit_status = WEXITSTATUS(status);
	return (shell->exit_status);
}

/*
pipe():  allows you to create a unidirectional communication channel,
commonly referred to as a pipe, through which data can be passed from 
one process (the "writing" process) to another process (the "reading" process)
*/
int	ft_mini_pipe(t_mini *shell, t_token *tkn)
{
	int	pipefd[2];

	if (tkn->next)
	{
		pipe(pipefd);
		ft_mini_pipe(shell, tkn->next);
	}
	else
	{
		pipefd[0] = -1;
		pipefd[1] = shell->std_in;
	}
	if (pipefd[1] < 0)
		close(pipefd[1]);
	return (ft_exec_pipe(shell, tkn));
}
