/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnegro <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 20:22:04 by mnegro            #+#    #+#             */
/*   Updated: 2023/09/22 16:29:40 by mnegro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_img(t_mini *shell)
{
	char	*args[5];

	args[0] = "eog";
	args[1] = "--display=:0";
	args[2] = "--gtk-no-debug=unset";
	args[3] = "doge.jpg";
	args[4] = NULL;
	if (shell->img != 0)
		kill(shell->img, SIGTERM);
	shell->img = fork();
	if (!shell->img)
	{
		dup2(open("/dev/null", O_WRONLY), STDERR_FILENO);
		close(open("/dev/null", O_WRONLY));
		execve("/usr/bin/eog", args, NULL);
	}
}
