/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_multi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnegro <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 17:08:34 by mnegro            #+#    #+#             */
/*   Updated: 2023/09/04 21:22:21 by mnegro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_exec_pipe(t_mini *shell, t_token *tkn, int *fd, int unused)
{
	pid_t	pid;
	int		status;

	status = 0;
	pid = fork();
	if (!pid)
	{
		ft_exec_red(shell, tkn);
		if (shell->exit_status == 0)
		{
			ft_dup_pipe(shell, fd[IN], fd[OUT]);
			if (unused != -1)
				close(unused);
			ft_exec_toby(shell, tkn->toby);
			ft_post_red(shell);
		}
		ft_exit(shell, shell->exit_status, 1);
	}
	waitpid(pid, &status, WNOHANG);
	shell->exit_status = WEXITSTATUS(status);
	return (pid);
}

void	ft_wait_pipe(t_mini *shell)
{
	t_token	*tmp;

	tmp = shell->tkn;
	while (tmp)
	{
		waitpid(tmp->pid, &shell->exit_status, 0);
		tmp = tmp->next;
	}
}
	
int	ft(t_token *tmp, int *fd_pipe, int *fd, int *unused)
{
	int flag;

	if (tmp->next)
	{
		pipe(fd_pipe);
		fd[OUT] = fd_pipe[OUT];
		*unused = fd_pipe[IN];
		flag = 0;
	}
	else
	{
		*unused = -1;
		flag = 1;
	}
	return (flag);
}

void	ft_mini_pipe(t_mini *shell)
{
	t_token	*tmp;
	int		fd[2];
	int		fd_pipe[2];
	int		unused;

	tmp = shell->tkn;
	fd[IN] = shell->std_in;
	while (tmp)
	{
		if (ft(tmp, fd_pipe, fd, &unused))
			fd[OUT] = shell->std_out;
		tmp->pid = ft_exec_pipe(shell, tmp, fd, unused);
		if (fd[IN] != shell->std_in)
			close(fd[IN]);
		close(fd_pipe[OUT]);
		fd[IN] = fd_pipe[IN];
		tmp = tmp->next;
	}
	close(fd_pipe[0]);
	ft_wait_pipe(shell);
}
