/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnegro <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 18:37:24 by mnegro            #+#    #+#             */
/*   Updated: 2023/08/29 18:27:07 by mnegro           ###   ########.fr       */
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

void	ft_exit(t_mini *shell, int n)
{
	free(shell->line);
	free(shell->history);
	ft_clear_tkn(&shell->tkn);
	ft_clear_env(&shell->envp);
	ft_freematrix(shell->envp_mtx);
	ft_clear_vbl(&shell->vbl);
	free(shell->bin);
	if (n != 0)
		exit (n);
	ft_putstr_fd("exit", 1);
	exit (n);
}

void	ft_vbl(t_mini *shell, char *cmd, int n)
{
	char	*key;
	char	*value;
	t_env	*tmp;

	key = ft_key(cmd);
	value = ft_value(cmd);
	ft_free(&cmd);
	tmp = shell->envp;
	while (tmp)
	{
		if (!ft_strncmp(key, tmp->key, ft_strlen(key) + 1))
		{
			ft_free(&tmp->value);
			tmp->value = value;
			tmp->vbl = ft_key_value(key, value);
			return ;
		}
		tmp = tmp->next;
	}
	if (n == 0)
		ft_backnew_vbl(&shell->vbl, key, value);
	else if (n == 1)
		ft_backnew_env(&shell->envp, key, value);
}
