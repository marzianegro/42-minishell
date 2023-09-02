/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_multi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnegro <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 17:08:34 by mnegro            #+#    #+#             */
/*   Updated: 2023/09/02 17:29:41 by mnegro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* The pipe() function  allows you to create a unidirectional communication
	channel, commonly referred to as a pipe, through which data can be
	passed from one process (the "writing" process) to another
	process (the "reading" process)*/
int	ft_mini_pipe(t_mini *shell, t_token *tkn)
{
	int	fd_pipe[2];

	if (tkn->next)
	{
		pipe(fd_pipe);
		ft_mini_pipe(shell, tkn->next);
	}
	else
	{
		fd_pipe[0] = -1;
		fd_pipe[1] = shell->fd_in;
	}
	if (fd_pipe[1] < 0)
		close(fd_pipe[1]);
	return (ft_exec_pipe(shell, tkn, fd_pipe[0], shell->fd_out));
}

int	ft_exec_pipe(t_mini *shell, t_token *tkn, int fd_old, int fd_new)
{
	pid_t	pid;
	int		pipe;
	int		status;

	pid = fork();
	pipe = 0;
	status = 0;
	if (!pid)
	{
		pipe = ft_exec_red(shell, tkn);
		if (!pipe)
		{
			ft_dup_fd(shell, fd_old, fd_new);
			pipe = ft_exec_toby(shell, tkn->toby);
			ft_close_fd(fd_old, fd_new, 0);
		}
		ft_exit(shell, shell->exit_status);
	}
	wait(&status);
	shell->exit_status = WEXITSTATUS(status);
	return (shell->exit_status);
}

