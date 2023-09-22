/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnegro <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 18:37:24 by mnegro            #+#    #+#             */
/*   Updated: 2023/09/22 16:28:57 by mnegro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_export(t_mini *shell)
{
	t_env	*tmp;
	int		i;

	i = 1;
	tmp = shell->envp;
	if (!shell->tkn->toby[i])
	{
		while (tmp)
		{
			if (tmp->value)
				printf("declare -x %s=\"%s\"\n", tmp->key, tmp->value);
			else
				printf("declare -x %s\n", tmp->key);
			tmp = tmp->next;
		}
	}
	else
	{
		while (shell->tkn->toby[i])
		{
			ft_exp_vbl(shell, i);
			i++;
		}
	}
}

void	ft_env(t_mini *shell)
{
	t_env	*tmp;

	tmp = shell->envp;
	while (tmp)
	{
		if (tmp->value)
			printf("%s\n", tmp->vbl);
		tmp = tmp->next;
	}
}

void	ft_exit_cmd(t_mini *shell, char *cmd)
{
	int	code;
	int	i;

	i = 0;
	ft_putstr_fd("exit\n", 1);
	if (cmd)
	{
		if (cmd[i] == '+' || cmd[i] == '-')
			i++;
		while (cmd[i] >= '0' && cmd[i] <= '9')
			i++;
		if (cmd[i] != '\0')
		{
			code = 2;
			ft_putstr_fd("perroshell: exit: ", 2);
			ft_putstr_fd(cmd, 2);
			ft_putstr_fd(": numeric argument required\n", 2);
		}
		else
			code = ft_atoi(cmd);
	}
	else
		code = 0;
	ft_exit(shell, code, 0);
}

void	ft_exit(t_mini *shell, int code, int child)
{
	ft_free(&shell->line);
	ft_free(&shell->history);
	ft_clear_tkn(&shell->tkn);
	ft_clear_env(&shell->envp);
	ft_clear_vbl(&shell->vbl);
	ft_free(&shell->bin);
	if (child == 0)
		kill(shell->img, SIGTERM);
	exit(code);
}

void	ft_vbl(t_mini *shell, char *cmd, int n)
{
	char	*key;
	char	*value;
	t_env	*tmp;

	key = ft_key(cmd);
	value = ft_value(cmd);
	tmp = shell->envp;
	while (tmp)
	{
		if (!ft_strncmp(key, tmp->key, ft_strlen(key) + 1))
		{
			ft_free(&tmp->value);
			tmp->value = value;
			ft_free(&tmp->vbl);
			tmp->vbl = ft_key_value(key, value);
			ft_free(&key);
			return ;
		}
		tmp = tmp->next;
	}
	if (n == 0)
		ft_backnew_vbl(&shell->vbl, key, value);
	else if (n == 1)
		ft_backnew_env(&shell->envp, key, value);
}
