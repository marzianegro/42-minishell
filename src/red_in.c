/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnegro <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 15:21:59 by mnegro            #+#    #+#             */
/*   Updated: 2023/09/01 18:02:07 by mnegro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* <: Redirects standard input from a file.
	<<: Allows you to provide multiple lines of input to a command. */

// <
/* If -2, no file has been opened, otherwise it means that another
	file is about to be opened and the previous one needs to be closed.
	If -1 there was an error */
int	ft_file_input(t_mini *shell, char *file)
{
	if (!file[0])
	{
		ft_putstr_fd("bash: syntax error near unexpected token `newline'", 2);
		return (1);
	}
	if (shell->fd_in != -1 && shell->fd_in != -2)
		close(shell->fd_in);
	shell->fd_in = open(file, O_RDONLY);
	if (shell->fd_in == -1)
		return (1);
	return (0);
}

// <<
