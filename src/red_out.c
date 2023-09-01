/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_out.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnegro <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 15:22:07 by mnegro            #+#    #+#             */
/*   Updated: 2023/09/01 18:01:25 by mnegro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*	>: Redirects standard output to a file. If the file doesn't exist,
	it's created; if it exists, it's overwritten.
	>>: Redirects standard output to a file, but appends to the file
	instead of overwriting it. */

// >
/* Opens the file in write-only mode, creating if it doesn't exist,
	and truncating its content */
/* If -2, no file has been opened, otherwise it means that another
	file is about to be opened and the previous one needs to be closed.
	If -1 there was an error */
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

// >>
