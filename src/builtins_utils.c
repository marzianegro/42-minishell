/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnegro <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 15:39:01 by mnegro            #+#    #+#             */
/*   Updated: 2023/08/21 17:58:57 by mnegro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_check_vbl(char *str)
{
	int	i;

	i = 0;
	if (str && (ft_is_key(str[0], 0) || str[0] == '='))
		return (1);
	while (str && str[i] != '=')
	{
		if (ft_is_key(str[i], 1))
			return (1);
		i++;
	}
	return (0);
}

char	*ft_key(char *str)
{
	int		i;
	int		len;
	char	*key;

	i = 0;
	len = 0;
	while (str && str[i] != '=')
	{
		len++;
		i++;
	}
	key = ft_substr(str, 0, len);
	return (key);
}

char	*ft_value(char *str)
{
	int		i;
	int		len;
	char	*value;

	i = 0;
	len = 0;
	while (str && str[i] != '=')
		i++;
	if (str && str[i] == '=')
		i++;
	while (str && str[i])
	{
		len++;
		i++;
	}
	value = ft_substr(str, i - len, len);
	return (value);
}

void	ft_set_exp(t_mini *shell)
{
	int			i;
	int			flag;
	t_variable	*tmp;

	i = 1;
	flag = 0;
	tmp = shell->vbl;
	while (tmp && tmp->next)
	{
		if (ft_strncmp(tmp->key, shell->tkn->toby[i],
				ft_strlen(tmp->key + 1)))
			tmp = tmp->next;
		else
			flag = 1;
	}
	if (flag == 0)
		ft_backnew_env(&shell->envp, tmp->key, tmp->value);
	else
		ft_backnew_env(&shell->envp, shell->tkn->toby[i], tmp->value);
}

void	ft_backnew_vbl(t_variable **vbl, char *key, char *value)
{
	t_variable	*newnode;
	t_variable	*tmp;

	newnode = (t_variable *)ft_calloc(1, sizeof(t_variable));
	if (!newnode)
		return ;
	newnode->key = key;
	newnode->value = value;
	newnode->next = NULL;
	if (!*vbl)
	{
		*vbl = newnode;
		return ;
	}
	tmp = *vbl;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = newnode;
}
