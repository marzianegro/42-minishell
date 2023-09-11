/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnegro <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 16:06:17 by mnegro            #+#    #+#             */
/*   Updated: 2023/09/04 16:13:01 by mnegro           ###   ########.fr       */
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

void	ft_del_env(t_env *envp, t_env *del)
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

void	ft_del_vbl(t_variable *vbl, t_variable *del)
{
	if (!vbl)
		return ;
	while (vbl && vbl->next != del)
		vbl = vbl->next;
	if (vbl)
	{
		vbl->next = del->next;
		free(del);
	}
}

