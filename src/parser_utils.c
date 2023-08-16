/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnegro <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 15:37:32 by mnegro            #+#    #+#             */
/*   Updated: 2023/08/16 15:48:14 by mnegro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_stoppers(char *str, int i)
{
	if (str[i] == '"' || str[i] == '$' || str[i] == '\'')
		return (1);
	return (0);
}

void	ft_handle_stoppers(char **mtx, int x, int y, t_parse *prs)
{
	if (!ft_stoppers(mtx[y], x))
	{
		if (prs->len != 0)
		{
			ft_new_str(mtx[y], prs->new, x - prs->len, prs->len);
			prs->len = 0;
		}
		if (mtx[y][x] == '\'')
			ft_single_quotes(mtx, x, y, prs);
		else if (mtx[y][x] == '"')
			ft_double_quotes(mtx, x, y, prs);
		else if (mtx[y][x] == '$')
			ft_variables(mtx, x, y, prs);
	}
}

void	ft_single_quotes(char **mtx, int x, int y, t_parse *prs)
{
	x++;
	while (mtx[y][x] != '\'')
	{
		x++;
		prs->len++;
	}
	ft_new_str(mtx[y], prs->new, x - prs->len, prs->len);
	x++;
}

void	ft_double_quotes(char **mtx, int x, int y, t_parse *prs)
{
	x++;
	while (mtx[y][x] != '"')
	{
		if (mtx[y][x] == '$')
		{
			x++;
			if (!ft_is_key(mtx[y], x, 0))
				x++;
			else
			{
				ft_fix_key(&mtx[y][x], &prs);
				ft_get_key(&mtx[y], &prs);
				ft_expand(shell->envp, &prs);
				x += ft_strlen(prs.key);
			}
		}
		x++;
		prs->len++;
	}
	ft_new_str(mtx[y], prs->new, x - prs->len, prs->len);
}

void	ft_variables(char **mtx, int x, int y, t_parse *prs)
{
	x++;
	if (!ft_is_key(mtx[y], x, 0))
	{
		x++;
		continue ;
	}
	else
	{
		ft_get_key(&mtx[y], &prs);
		ft_expand(shell->envp, &prs);
	}
}
