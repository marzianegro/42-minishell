/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnegro <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 15:18:49 by mnegro            #+#    #+#             */
/*   Updated: 2023/08/30 17:03:47 by mnegro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_clear_env(t_env **envp)
{
	t_env	*ptr;

	if (!*envp)
		return ;
	while (*envp)
	{
		ptr = (*envp)->next;
		ft_free(&(*envp)->key);
		ft_free(&(*envp)->value);
		ft_free(&(*envp)->vbl);
		free(*envp);
		*envp = ptr;
	}
	*envp = NULL;
}

void	ft_clear_vbl(t_variable **vbl)
{
	t_variable	*ptr;

	if (!*vbl)
		return ;
	while (*vbl)
	{
		ptr = (*vbl)->next;
		ft_free(&(*vbl)->key);
		ft_free(&(*vbl)->value);
		free(*vbl);
		*vbl = ptr;
	}
	*vbl = NULL;
}

void	ft_del_vbl(t_env *envp, t_env *del)
{
	if (!envp)
		return ;
	while (envp && envp->next != del)
		envp = envp->next;
	if (envp)
	{
		envp->next = del->next;
		ft_free(&del->key);
		ft_free(&del->value);
		ft_free(&del->vbl);
		free(del);
	}
}

void	ft_exp_vbl(t_mini *shell, int i)
{
	char		*vbl;
	t_variable	*tmp;

	vbl = ft_strdup(shell->tkn->toby[i]);
	tmp = shell->vbl;
	while (tmp)
	{
		if (!ft_strncmp(vbl, tmp->key, ft_strlen(vbl) + 1))
		{
			ft_backnew_env(&shell->envp, tmp->key, tmp->value);
			return ;
		}
		else
			tmp = tmp->next;
	}
	if (ft_strfind(vbl, '=') && !ft_check_vbl(vbl))
		ft_vbl(shell, vbl, 1);
	else if (!ft_check_vbl(vbl))
		ft_backnew_env(&shell->envp, vbl, NULL);
}

void	ft_update_pwd(t_mini *shell)
{
	t_env	*tmp;
	char	*newpwd;

	tmp = shell->envp;
	newpwd = getcwd(NULL, 0);
	while (tmp)
	{
		while (ft_strncmp("PWD", tmp->key, 4))
			tmp = tmp->next;
		ft_free(&tmp->value);
		tmp->value = newpwd;
		return ;
	}
}
