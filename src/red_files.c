/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_files.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnegro <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 15:22:07 by mnegro            #+#    #+#             */
/*   Updated: 2023/09/22 16:32:19 by mnegro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_file_input(t_mini *shell, char *file)
{
	if (shell->fd_in != -1 && shell->fd_in != -2)
		close(shell->fd_in);
	shell->fd_in = open(file, O_RDONLY);
	if (shell->fd_in == -1)
	{
		ft_putstr_fd("perroshell: : ", 2);
		perror(file);
		shell->exit_status = 2;
		return ;
	}
}

int	ft_file_output(t_mini *shell, char *file, int a_or_c)
{
	if (shell->fd_out != -1 && shell->fd_out != -2)
		close(shell->fd_out);
	if (a_or_c == 1)
		shell->fd_out = open(file, O_WRONLY | O_CREAT | O_APPEND, 0666);
	if (a_or_c == 2)
		shell->fd_out = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (shell->fd_out == -1)
	{
		ft_putstr_fd("perroshell: : ", 2);
		perror(file);
		shell->exit_status = 2;
		return (shell->exit_status);
	}
	return (0);
}
