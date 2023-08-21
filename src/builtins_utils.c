/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnegro <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 15:39:01 by mnegro            #+#    #+#             */
/*   Updated: 2023/08/19 13:47:15 by mnegro           ###   ########.fr       */
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
		if (ft_strncmp(shell->tkn->toby[i], tmp->key,
				ft_strlen(shell->tkn->toby[i] + 1)))
			tmp = tmp->next;
		else
			flag = 1;
	}
	if (flag == 0)
		ft_addback_new(shell->envp, tmp->key, tmp->value);
	else
		ft_addback_new(shell->envp, shell->tkn->toby[i], NULL);
}

