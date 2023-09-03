/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnegro <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 17:22:43 by mnegro            #+#    #+#             */
/*   Updated: 2023/09/03 14:46:23 by mnegro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* The dup2() function duplicates an open file descriptor to another file
	descriptor; used for redirecting input and output streams, changing
	the target of a file descriptor, or setting up communication
	between processes */
void	ft_dup_fd(t_mini *shell, int fd_old, int fd_new)
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

void	ft_close_fd(int fd_old, int fd_new)
{
	if (fd_old != -1 && fd_old != -2)
		close(fd_old);
	if (fd_new != -1 && fd_new != -2)
		close(fd_new);
}

void	ft_post_red(t_mini *shell)
{
	if (shell->fd_in != -1 && shell->fd_in != -2)
		close(shell->fd_in);
	shell->fd_in = -2;
	dup2(shell->std_in, 0);
	if (shell->fd_out != -1 && shell->fd_out != -2)
		close(shell->fd_out);
	shell->fd_out = -2;
	dup2(shell->std_out, 1);
}

