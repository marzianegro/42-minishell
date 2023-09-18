/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnegro <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 15:47:55 by mnegro            #+#    #+#             */
/*   Updated: 2023/09/11 20:24:31 by mnegro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_find_bin(t_mini *shell, char *cmd)
{
	t_env	*tmp;
	char	*path;
	char	**dir;
	char	*tmp_bin;
	int		y;

	y = -1;
	tmp = shell->envp;
	while (tmp && ft_strncmp("PATH", tmp->key, 5))
		tmp = tmp->next;
	if (!tmp)
		return (1);
	path = ft_strdup(tmp->value);
	if (!path)
		return (1);
	dir = ft_split(path, ':');
	while (dir[++y])
	{
		tmp_bin = ft_strjoin(dir[y], "/");
		shell->bin = ft_strjoin_gnl(tmp_bin, cmd);
		if (!access(shell->bin, F_OK))
			return (ft_freematrix(dir), 0);
		ft_free(&shell->bin);
	}
	return (ft_freematrix(dir), 1);
}

void	ft_convert_envp(t_mini *shell)
{
	int		y;
	int		size;
	t_env	*tmp;

	y = 0;
	size = 0;
	tmp = shell->envp;
	while (tmp)
	{
		size++;
		tmp = tmp->next;
	}
	shell->envp_mtx = (char **)ft_calloc(size + 1, sizeof(char *));
	tmp = shell->envp;
	while (shell->envp_mtx[y] && tmp)
	{
		shell->envp_mtx[y] = ft_strdup(tmp->vbl);
		y++;
		tmp = tmp->next;
	}
}

void	ft_exec_binary(t_mini *shell, char *cmd)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (!pid)
	{
		if (ft_find_bin(shell, cmd))
			shell->bin = ft_strdup(cmd);
		ft_convert_envp(shell);
		execve(shell->bin, shell->tkn->toby, shell->envp_mtx);
		ft_freematrix(shell->envp_mtx);
		if (WEXITSTATUS(EXIT_FAILURE) != 1)
		{
			ft_putstr_fd(cmd, 2);
			ft_putstr_fd(": command not found\n", 2);
			ft_exit(shell, 127, 1);
		}
		perror(cmd);
		ft_exit(shell, EXIT_FAILURE, 1);
	}
	waitpid(pid, &status, 0);
	shell->exit_status = WEXITSTATUS(status);
}
