/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnegro <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 15:18:49 by mnegro            #+#    #+#             */
/*   Updated: 2023/09/04 16:17:29 by mnegro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
			ft_backnew_env(&shell->envp, ft_strdup(tmp->key),
				ft_strdup(tmp->value));
			free(vbl);
			return ;
		}
		else
			tmp = tmp->next;
	}
	if (ft_strfind(vbl, '=') && !ft_check_vbl(vbl))
		ft_vbl(shell, vbl, 1);
	else if (!ft_check_vbl(vbl))
		ft_backnew_env(&shell->envp, ft_strdup(vbl), NULL);
	free(vbl);
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
