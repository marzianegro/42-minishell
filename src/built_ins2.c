/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnegro <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 18:37:24 by mnegro            #+#    #+#             */
/*   Updated: 2023/08/21 17:59:01 by mnegro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* I cast a void mi servivano solo per vedere se tutto compilava correttamente,
	si possono tranquillamente togliere una volta che si inizia a lavorare
	effettivamente sulle funzioni */
void	ft_clear(t_mini *shell, char **mtx)
{
	(void)shell;
	(void)mtx;
}

void	ft_export(t_mini *shell)
{
	t_env	*tmp;

	tmp = shell->envp;
	if (!shell->tkn->toby[1])
	{
		while (tmp && tmp->next)
		{
			printf("declare -x %s=\"%s\"\n", tmp->key, tmp->value);
			tmp = tmp->next;
		}
	}
	else
		ft_set_exp(shell);
}

void	ft_env(t_mini *shell)
{
	t_env	*tmp;

	tmp = shell->envp;
	while (tmp && tmp->next)
	{
		if (tmp->value)
			printf("%s\n", tmp->vbl);
		tmp = tmp->next;
	}
}

void	ft_exit(t_mini *shell, char **mtx)
{
	(void)shell;
	(void)mtx;
}

void	ft_vbl(t_mini *shell, char *cmd)
{
	char		*key;
	char		*value;
	t_variable	*tmp;

	key = ft_key(cmd);
	value = ft_value(cmd);
	tmp = shell->vbl;
	while (tmp && tmp->next)
	{
		if (!ft_strncmp(key, tmp->key, ft_strlen(key) + 1))
		{
			ft_free(&tmp->value);
			tmp->value = value;
			return ;
		}
		tmp = tmp->next;
	}
	ft_backnew_vbl(&shell->vbl, key, value);
}
