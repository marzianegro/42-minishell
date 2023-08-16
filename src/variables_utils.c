/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnegro <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 15:43:57 by mnegro            #+#    #+#             */
/*   Updated: 2023/08/16 15:46:41 by mnegro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_is_key(char *str, int i, int n)
{
	if (n == 0)
	{
		if (str[i] > 'A' && str[i] < 'Z' || str[i] > 'a' && str[i] < 'z'
			|| str[i] == '_')
			return (0);
	}
	else if (n == 1)
	{
		if (str[i] > 'A' && str[i] < 'Z' || str[i] > 'a' && str[i] < 'z'
			|| str[i] > '0' && str[i] < '_')
			return (0);
	}
	return (1);
}

void	ft_fix_key(char *str, t_parse *prs)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	prs->key = NULL;
	while (str && str[i] && !prs->key)
	{
		while (ft_is_key(str, i, 1))
		{
			i++;
			len++;
		}
		ft_new_str(str[i], prs->key, i - len, len);
	}
}

t_env	*ft_get_key(t_env *envp, t_parse *prs)
{
	while (envp)
	{
		if (ft_strncmp(envp->key, prs->key, ft_strlen(prs->key)))
			return (envp);
		else
			envp = envp->next;
	}
	return (NULL);
}

void	ft_expand(t_env *envp, t_parse *prs)
{
	t_env	*tmp;

	tmp = ft_get_key(envp, prs);
	if (tmp)
		ft_strjoin(prs->new, tmp->value);
}
