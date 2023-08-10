/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnegro <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 10:42:51 by mnegro            #+#    #+#             */
/*   Updated: 2023/08/10 14:14:08 by mnegro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_count_quotes(char *str, t_parse *prs)
{
	int	i;

	i = 0;
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

char	*ft_new_str(char *str, int start, int len)
{
	char	*tmp;
	char	*jnd;

	tmp = ft_substr(str, start, len);
	jnd = ft_strjoin(jnd, tmp);
	free(tmp);
	return (jnd);
}
