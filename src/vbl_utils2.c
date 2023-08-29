/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vbl_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnegro <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 14:33:46 by mnegro            #+#    #+#             */
/*   Updated: 2023/08/24 15:01:50 by mnegro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	{
		if (!ft_strncmp(key, tmp->key, ft_strlen(key) + 1))
			return ;
		tmp = tmp->next;
	}
	if (!ft_strncmp(key, tmp->key, ft_strlen(key) + 1))
		return ;
	tmp->next = newnode;
}

int	ft_check_vbl(char *str)
{
	int	i;

	i = 0;
	if (str && (ft_is_key(str[0], 0) || str[0] == '='))
		return (1);
	while (str && str[i] && str[i] != '=')
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

/* Not sure if this function is actually useful, since I haven't used it yet */
int	ft_norm_vbl(char **mtx, t_mini *shell, t_parse *prs)
{
	prs->x++;
	if (ft_is_key(mtx[prs->y][prs->x], 0))
	{
		prs->x++;
		return (1);
	}
	else
	{
		ft_fix_key(&(mtx[prs->y][prs->x]), prs);
		ft_get_key(shell->envp, prs);
		ft_expand(shell->envp, prs);
		prs->x += ft_strlen(prs->key);
	}
	return (0);
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
