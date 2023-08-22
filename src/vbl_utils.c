/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vbl_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnegro <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 15:43:57 by mnegro            #+#    #+#             */
/*   Updated: 2023/08/21 17:37:41 by mnegro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_is_key(char c, int n)
{
	if (n == 0)
	{
		if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')
			|| c == '_')
			return (0);
	}
	else if (n == 1)
	{
		if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')
			|| (c >= '0' && c <= '9') || c == '_')
			return (0);
	}
	return (1);
}

void	ft_new_key(char *str, char **new, int start, int len)
{
	char	*tmp;

	tmp = ft_substr(str, start, len);
	*new = ft_strjoin(*new, tmp);
	free(tmp);
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
		while (!ft_is_key(str[i], 1))
		{
			i++;
			len++;
		}
		ft_new_key(str, &prs->key, i - len, len);
	}
}

t_env	*ft_get_key(t_env *envp, t_parse *prs)
{
	while (envp)
	{
		if (!ft_strncmp(envp->key, prs->key, ft_strlen(prs->key) + 1))
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
		prs->new = ft_strjoin(prs->new, tmp->value);
}
