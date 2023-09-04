/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_files.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnegro <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 15:22:07 by mnegro            #+#    #+#             */
/*   Updated: 2023/09/04 14:47:41 by mnegro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* OUTPUT REDIRECTION
	>: Redirects standard output to a file. If the file doesn't exist,
	it's created; if it exists, it's overwritten.
	>>: Redirects standard output to a file, but appends to the file
	instead of overwriting it. */
/* INPUT REDIRECTION
	<: Redirects standard input from a file.
	<<: Allows you to provide multiple lines of input to a command. */

/* If the fd is equal to -2, it means no file has been opened, otherwise
	another file is about to be opened and the previous one needs to be closed.
	If the fd is -1, it means there was an error */
int	ft_file_output(t_mini *shell, char *file, int a_or_c)
{
	if (!file[0])
		return (1);
	if (shell->fd_out != -1 && shell->fd_out != -2)
		close(shell->fd_out);
	if (a_or_c == 1)
		shell->fd_out = open(file, O_WRONLY | O_CREAT | O_APPEND, 0666);
	if (a_or_c == 2)
		shell->fd_out = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	return (0);
}

void	ft_file_input(t_mini *shell, char *file)
{
	if (!file[0])
	{
		ft_putstr_fd("miniscam: syntax error near "
			"unexpected token `newline'\n", 2);
		shell->exit_status = 1;
		return ;
	}
	if (shell->fd_in != -1 && shell->fd_in != -2)
		close(shell->fd_in);
	shell->fd_in = open(file, O_RDONLY);
	if (shell->fd_in == -1)
	{
		ft_putstr_fd("miniscam: ", 2);
		perror(file);
		shell->exit_status = 2;
	}
}

