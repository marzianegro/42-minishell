/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnegro <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 14:50:58 by mnegro            #+#    #+#             */
/*   Updated: 2023/09/01 17:01:39 by mnegro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_init_history(t_mini *shell)
{
	char	*line;

	shell->history = ft_strjoin(getenv("HOME"), "/.mini_history");
	shell->history_fd = open(shell->history, O_RDWR | O_CREAT, 0644);
	line = get_next_line(shell->history_fd);
	if (!line)
		return ;
	else
	{
		while (line)
		{
			line[ft_strlen(line) - 1] = 0;
			add_history(line);
			free(line);
			line = get_next_line(shell->history_fd);
		}
	}
}

t_env	*ft_init_env(char **mtx)
{
	t_env	*envp;
	int		y;

	y = 0;
	envp = NULL;
	while (mtx[y])
	{
		ft_set_env(mtx, y, &envp);
		y++; 
	}
	return (envp);
}

void	ft_init_shell(t_mini *shell, char **envp)
{
	shell->tkn = NULL;
	ft_init_history(shell);
	shell->envp = ft_init_env(envp);
	shell->envp_mtx = NULL;
	shell->vbl = NULL;
	shell->bin = NULL;
	shell->std_in = 0;
	shell->std_out = 1;
	shell->fd_in = 0;
	shell->fd_out = -1;
	ft_save_exit(shell, 0);
	shell->exit_status = 0;
}
