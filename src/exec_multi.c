/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_multi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnegro <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 17:08:34 by mnegro            #+#    #+#             */
/*   Updated: 2023/09/01 17:07:21 by mnegro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_fd_close(int fd_old, int fd_new, int nbr)
{
	if (fd_old != -2)
		if (fd_old != -1)
			close(fd_old);
	if (fd_new != -2)
		if (fd_new != -1)
			close(fd_new);
	if (nbr == -2)
		return (1);
	// if (fd_old != -1 && fd_old != -2)
	// 	close(fd_old);
	// if (fd_new != -1 && fd_new != -2)
	// 	close(fd_new);
	return (nbr);
}

/* The dup2() function duplicates an open file descriptor to another file
	descriptor; used for redirecting input and output streams, changing
	the target of a file descriptor, or setting up communication
	between processes */
void	ft_fd_dup(t_mini *shell, int fd_old, int fd_new)
{
	if (fd_old != -1)
		dup2(fd_old, 0);
	else if (shell->fd_in != -2)
		dup2(shell->fd_in, 0);
	if (fd_new != -1)
		dup2(fd_new, 1);
	else if (shell->fd_out != -2)
		dup2(shell->fd_out, 1);
}

void	ft_post_exec(t_mini *shell)
{
	if (shell->fd_in != -2 || shell->fd_out != -2)
	{
		if (shell->fd_in != -1)
			close(shell->fd_in);
		shell->fd_in = -2;
		dup2(shell->std_in, 0);
		if (shell->fd_out != -1)
			close(shell->fd_out);
		shell->fd_out = -2;
		dup2(shell->std_out, 1);
	}
	ft_fd_close(shell->fd_in, shell->fd_out, 0);
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
			ft_fd_dup(shell, fd_old, fd_new);
			pipe = ft_exec_toby(shell, tkn->toby);
			ft_fd_close(fd_old, fd_new, 0);
		}
		ft_exit(shell, shell->exit_status);
	}
	wait(&status);
	shell->exit_status = WEXITSTATUS(status);
	return (shell->exit_status);
}

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
