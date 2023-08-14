/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_rt.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnegro <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 16:10:03 by mnegro            #+#    #+#             */
/*   Updated: 2023/08/14 12:42:32 by mnegro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_parse_rt(t_rt **rt)
{
	ft_iter(*rt, ft_spaces);
	ft_iter(*rt, ft_quotes);
}

void	ft_spaces(char **mtx)
{
	int		x;
	int		y;
	t_parse	prs;

	y = 0;
	prs.len = 0;
	while (mtx[y])
	{
		x = 0;
		prs.new = NULL;
		ft_count_qs(mtx[y], &prs);
		while (mtx[y][x])
		{
			if (prs.sq == 0 || prs.dq == 0)
			{
				while (mtx[y][x] && ft_is_space(mtx[y], x))
					x++;
				while (mtx[y][x] && !ft_is_space(mtx[y], x))
				{
					x++;
					prs.len++;
				}
				ft_new_str(mtx[y], &prs.new, x - prs.len, prs.len);
				prs.len = 0;
			}
		}
		if (prs.new)
			mtx[y] = prs.new;
		y++;
	}
}

void	ft_quotes(char **mtx)
{
	int		x;
	int		y;
	t_parse	prs;

	y = 0;
	prs.len = 0;
	while (mtx[y])
	{
		x = 0;
		prs.new = NULL;
		ft_count_qs(mtx[y], &prs);
		while (mtx[y][x])
		{
			if (prs.sq != 0 || prs.dq != 0)
			{
				while (mtx[y][x] && ft_is_quotes(mtx[y], x))
					x++;
				while (mtx[y][x] && !ft_is_quotes(mtx[y], x))
				{
					x++;
					prs.len++;
				}
				ft_new_str(mtx[y], &prs.new, x - prs.len, prs.len);
				prs.len = 0;
			}
		}
		if (prs.new)
			mtx[y] = prs.new;
		y++;
	}
}

// void	ft_variables(char **mtx)
// {
// }
