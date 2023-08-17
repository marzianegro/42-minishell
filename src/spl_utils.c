/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spl_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnegro <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 16:14:13 by mnegro            #+#    #+#             */
/*   Updated: 2023/08/17 16:01:56 by mnegro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_is_stop(char c, int n)
{
	if (n == 1)
	{
		if (c == '\0' || c == ' ' || c == '<' || c == '>' || c == '|')
			return (1);
	}
	else if (n == 2)
	{
		if (c == '\0' || c == ' ' || c == '|')
			return (1);
	}
	else if (n == 3)
	{
		if (c == '\0' || c == '|')
			return (1);
	}
	return (0);
}

int	ft_whether_quotes(t_split *spl)
{
	if ((spl->sq == 0 || spl->sq % 2 == 0)
		&& (spl->dq == 0 || spl->dq % 2 == 0))
		return (1);
	return (0);
}

void	ft_check_quotes(char *str, char c, int *len)
{
	*len += 1;
	while (str[*len] != c)
		*len += 1;
	*len += 1;
}

void	ft_check_redirects(char *str, int *i)
{
	while (str[*i] == '<' || str[*i] == '>')
	{
		*i += 1;
		if ((str[*i - 1] == '<' && str[*i] == '<')
			|| (str[*i - 1] == '>' && str[*i] == '>'))
			*i += 1;
		while (str[*i] == ' ')
			*i += 1;
		while (!ft_is_stop(str[*i], 1))
		{
			if (str[*i] == '"')
				ft_check_quotes(str, '"', i);
			else if (str[*i] == '\'')
				ft_check_quotes(str, '\'', i);
			else
				*i += 1;
		}
	}
}

void	ft_regular_red(char *line, t_split *spl)
{
	if (line[spl->i] == '"' && (spl->sq == 0 || spl->sq % 2 == 0))
		spl->dq++;
	if (line[spl->i] == '\'' && (spl->dq == 0 || spl->dq % 2 == 0))
		spl->sq++;
	spl->i++;
	while ((line[spl->i] == '|' || line[spl->i] == ' ')
		&& !ft_whether_quotes(spl))
		spl->i++;
}
