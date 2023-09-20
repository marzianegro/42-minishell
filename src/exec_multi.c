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

int	ft_mini_pipe(t_mini *shell, t_token *tkn, int fd_out)
{
	int	fd_pipe[2];

	if (tkn->next)
	{
		pipe(fd_pipe);
		ft_mini_pipe(shell, tkn->next, fd_pipe[1]);
	}
	else
	{
		fd_pipe[0] = shell->std_in;
		fd_pipe[1] = -1;
	}
	if (fd_pipe[1] != -1)
		close(fd_pipe[1]);
	return (ft_exec_pipe(shell, tkn, fd_pipe[0], fd_out));
}

int	ft_exec_pipe(t_mini *shell, t_token *tkn, int fd_in, int fd_out)
{
	pid_t	pid;
	int		status;

	status = 0;
	pid = fork();
	if (!pid)
	{
		ft_exec_red(shell, tkn);
		if (shell->exit_status != 0)
			ft_exit(shell, shell->exit_status, 1);
		ft_dup_pipe(shell, fd_in, fd_out);
		ft_exec_toby(shell, tkn->toby);
		ft_post_red(shell);
		ft_exit(shell, shell->exit_status, 1);
	}
	waitpid(pid, &status, 0);
	ft_dup_pipe(shell, shell->std_in, shell->std_out);
	shell->exit_status = WEXITSTATUS(status);
	return (shell->exit_status);
}

