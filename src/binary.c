/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnegro <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 15:47:55 by mnegro            #+#    #+#             */
/*   Updated: 2023/08/29 18:51:38 by mnegro           ###   ########.fr       */
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
	path = ft_strdup(tmp->value);
	if (!path)
		return (1);
	dir = ft_split(path, ':');
	while (dir[++y])
	{
		tmp_bin = ft_strjoin(dir[y], "/");
		shell->bin = ft_strjoin(tmp_bin, cmd);
		free(tmp_bin);
		if (!access(shell->bin, F_OK))
			return (ft_freematrix(dir), 0);
		free(shell->bin);
	}
	ft_freematrix(dir);
	return (1);
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
	shell->envp_mtx = (char **)ft_calloc(size, sizeof(char *));
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

	if (ft_find_bin(shell, cmd))
		shell->bin = ft_strdup(cmd);
	ft_convert_envp(shell);
	pid = fork();
	if (!pid)
	{
		execve(shell->bin, shell->tkn->toby, shell->envp_mtx);
		if (waitpid(pid, &status, 0) == -1)
		{
			ft_putstr_fd(cmd, 2);
			ft_putstr_fd(": command not found\n", 2);
			ft_exit(shell, -1);
		}
	}
	waitpid(pid, &status, 0);
	shell->exit_status = WEXITSTATUS(status);
}
