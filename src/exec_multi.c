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
/*
-1 means there was an error
-2 means that no file has been opened otherwise it means,
 another file is about to be opened and we need to close the previous one
*/

int	ft_close_fd(int oldfd, int newfd)
{
	int err_fd;
	int	returne;

	err_fd = 0;
	returne = 0;
	if (oldfd != -1 && oldfd != -2)
		close(oldfd);
	if (newfd != -1 && newfd != -2)
		close(newfd);
	if (err_fd != -1 && err_fd != -2)
		colse(err_fd);
	if (returne != -2)
		return (0);
	return (returne);
}

int	ft_pipe_exec(t_mini *shell, t_token *tkn, int oldfd, int newfd)
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
			ft_close_fd(oldfd, newfd);
		}
		free(shell); // forse è necessaria una funzione di free della shell
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
	int fd_out;
	
	(void) fd_out;
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
	return (ft_pipe_exec(shell, tkn, pipefd[0], fd_out));
}
