/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnegro <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 14:51:55 by mnegro            #+#    #+#             */
/*   Updated: 2023/09/04 15:16:59 by mnegro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_key_value(char *key, char *value)
{
	char	*tmp;
	char	*vbl;

	tmp = ft_strjoin(key, "=");
	vbl = ft_strjoin_gnl(tmp, value);
	// free(tmp);
	return (vbl);
}

void	ft_backnew_env(t_env **envp, char *key, char *value)
{
	t_env	*newnode;
	t_env	*tmp;

	newnode = (t_env *)ft_calloc(1, sizeof(t_env));
	if (!newnode)
		return ;
	newnode->key = key;
	newnode->value = value;
	newnode->vbl = ft_key_value(key, value);
	newnode->next = NULL;
	if (!*envp)
	{
		*envp = newnode;
		return ;
	}
	tmp = *envp;
	while (tmp->next)
	{
		if (!ft_strncmp(key, tmp->key, ft_strlen(key) + 1))
			return ;
		tmp = tmp->next;
	}
	if (!ft_strncmp(key, tmp->key, ft_strlen(key) + 1))
		return ;
	tmp->next = newnode;
}

void	ft_set_env(char **mtx, int y, t_env **envp)
{
	int		x;
	int		len;
	char	*key;
	char	*value;

	x = 0;
	len = 0;
	key = NULL;
	value = NULL;
	while (mtx[y][x])
	{
		while (mtx[y][x] != '=')
		{
			x++;
			len++;
		}
		key = ft_substr(mtx[y], 0, len);
		len = 0;
		while (mtx[y][++x])
			len++;
		value = ft_substr(mtx[y], x - len, len);
	}
	ft_backnew_env(envp, key, value);
}
