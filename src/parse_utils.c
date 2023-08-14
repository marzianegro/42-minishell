/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnegro <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 10:42:51 by mnegro            #+#    #+#             */
/*   Updated: 2023/08/14 11:49:11 by mnegro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_count_qs(char *str, t_parse *prs)
{
	int	i;

	i = 0;
	prs->sq = 0;
	prs->dq = 0;
	while (str && str[i])
	{
		if (str[i] == 34 && (prs->sq == 0 || prs->sq % 2 == 0))
			prs->dq++;
		if (str[i] == 39 && (prs->dq == 0 || prs->dq % 2 == 0))
			prs->sq++;
		i++;
	}
}

int	ft_is_quotes(char *str, int i)
{
	if (str[i] == 34 || str[i] == 39)
		return (1);
	return (0);
}

int	ft_is_space(char *str, int i)
{
	if (str[i] == 32)
		return (1);
	return (0);
}

void	ft_new_str(char *str, char **new, int start, int len)
{
	char	*tmp;

	tmp = ft_substr(str, start, len);
	*new = ft_strjoin(*new, tmp);
	free(tmp);
}
