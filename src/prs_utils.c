/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prs_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnegro <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 15:37:32 by mnegro            #+#    #+#             */
/*   Updated: 2023/08/30 17:03:44 by mnegro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_double_quotes(char **mtx, t_mini *shell, t_parse *prs)
{
	prs->x++;
	while (mtx[prs->y][prs->x] != '"')
	{
		if (mtx[prs->y][prs->x] == '$')
			ft_variables(mtx, shell, prs);
		else
		{
			prs->x++;
			prs->len++;
		}
	}
	ft_new_str(mtx[prs->y], prs);
	prs->x++;
	return (0);
}

int	ft_handle_stoppers(char **mtx, t_mini *shell, t_parse *prs)
{
	if (ft_stoppers(mtx[prs->y][prs->x]))
	{
		if (prs->len != 0)
			ft_new_str(mtx[prs->y], prs);
		if (mtx[prs->y][prs->x] == '\'')
			ft_single_quotes(mtx, prs);
		else if (mtx[prs->y][prs->x] == '"'
			&& ft_double_quotes(mtx, shell, prs))
			return (1);
		else if (mtx[prs->y][prs->x] == '$' && ft_variables(mtx, shell, prs))
			return (1);
	}
	return (0);
}

void	ft_new_str(char *str, t_parse *prs)
{
	char	*tmp;

	tmp = ft_substr(str, prs->x - prs->len, prs->len);
	prs->new = ft_strjoin(prs->new, tmp);
	prs->len = 0;
	free(tmp);
}

void	ft_single_quotes(char **mtx, t_parse *prs)
{
	prs->x++;
	while (mtx[prs->y][prs->x] != '\'')
	{
		prs->x++;
		prs->len++;
	}
	ft_new_str(mtx[prs->y], prs);
	prs->x++;
}

int	ft_stoppers(char c)
{
	if (c == '"' || c == '$' || c == '\'' || c == '\0')
		return (1);
	return (0);
}
