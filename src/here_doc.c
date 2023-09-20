/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnegro <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 15:09:32 by mnegro            #+#    #+#             */
/*   Updated: 2023/09/11 21:19:47 by mnegro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_kill_child(int n)
{
	static int	pid = 0;

	if (n == -1)
		pid = 0;
	else if (pid)
	{
		kill(pid, SIGKILL);
		pid = 0;
	}
	else if (n)
		pid = n;
	return (0);
}

void	ft_here_doc(t_mini *shell, char *delimiter, int fd)
{
	char	*line;
	char	*del;

	signal(SIGINT, ft_handler_here_doc);
	del = ft_strjoin(delimiter, "\n");
	line = "";
	while (line)
	{
		ft_putstr_fd("> ", 1);
		line = get_next_line(0);
		if (!ft_strncmp(line, del, ft_strlen(del) + 1))
		{
			free(line);
			free(del);
			break ;
		}
		ft_putstr_fd(line, fd);
		free(line);
	}
	ft_exit(shell, 0, 1);
}

int	ft_handle_here_doc(t_mini *shell, char *delimiter)
{
	pid_t	pid;
	int		fd_tmp;

	signal(SIGINT, ft_handler_here_doc);
	unlink("/tmp/here_doc");
	fd_tmp = open("/tmp/here_doc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	pid = fork();
	if (!pid)
		ft_here_doc(shell, delimiter, fd_tmp);
	ft_kill_child(pid);
	waitpid(pid, &shell->exit_status, 0);
	ft_kill_child(-1);
	signal(SIGINT, ft_handler_exec);
	close(fd_tmp);
	shell->fd_in = open("/tmp/here_doc", O_RDONLY);
	return (0);
}
