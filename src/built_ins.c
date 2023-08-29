/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnegro <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 18:02:01 by mnegro            #+#    #+#             */
/*   Updated: 2023/08/24 18:29:34 by mnegro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_cd(t_mini *shell)
{
	char	*path;

	path = shell->tkn->toby[1];
	if (!path)
		chdir(getenv("HOME"));
	else
	{
		if (chdir(path) == -1)
			return (1);
	}
	ft_update_pwd(shell);
	return (0);
}

void	ft_history(t_mini *shell)
{
	char	*line;
	int		n;

	shell->history_fd = open(shell->history, O_RDONLY);
	line = get_next_line(shell->history_fd);
	n = 0;
	while (line)
	{
		printf("%d  %s", n, line);
		n++;
		free(line);
		line = get_next_line(shell->history_fd);
	}
}

void	ft_echo(char **mtx)
{
	int	y;
	int	flag;

	y = 1;
	flag = 0;
	if (!mtx[y])
		printf("\n");
	while (mtx[y])
	{
		if (!ft_strncmp("-n", mtx[1], 3) && flag == 0)
		{
			flag = 1;
			if (!mtx[++y])
				break ;
		}
		if (mtx[y + 1])
			printf("%s ", mtx[y]);
		else if (!mtx[y + 1])
		{
			printf("%s", mtx[y]);
			if (flag != 1)
				printf("\n");
		}
		y++;
	}
}

void	ft_unset(t_mini *shell)
{
	int		i;
	t_env	*tmp;

	i = 1;
	while (shell->tkn->toby[i])
	{
		tmp = shell->envp;
		while (tmp)
		{
			if (!ft_strncmp(shell->tkn->toby[i], tmp->key,
					ft_strlen(shell->tkn->toby[i]) + 1))
				ft_del_vbl(shell->envp, tmp);
			tmp = tmp->next;
		}
		i++;
	}
}

void	ft_pwd(t_mini *shell)
{
	t_env	*tmp;

	tmp = shell->envp;
	while (tmp && tmp->next)
	{
		if (!ft_strncmp("PWD", tmp->key, 4))
			printf("%s\n", tmp->value);
		tmp = tmp->next;
	}
}
