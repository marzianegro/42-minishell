/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnegro <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 17:22:43 by mnegro            #+#    #+#             */
/*   Updated: 2023/09/22 16:29:29 by mnegro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_dup_red(t_mini *shell, int fd_old, int fd_new)
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

void	ft_dup_pipe(t_mini *shell, int fd_in, int fd_out)
{
	if (shell->fd_in != -2)
		dup2(shell->fd_in, 0);
	else if (fd_in != -1)
		dup2(fd_in, 0);
	if (shell->fd_out != -2)
		dup2(shell->fd_out, 1);
	else if (fd_out != -1)
		dup2(fd_out, 1);
	close(fd_in);
	close(fd_out);
}
