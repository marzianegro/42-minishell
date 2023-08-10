/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_rt.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnegro <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 16:10:03 by mnegro            #+#    #+#             */
/*   Updated: 2023/08/10 14:14:09 by mnegro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_parse_rt(t_rt **rt)
{
	ft_iter(*rt, ft_quotes);
}

// void	ft_spaces(char **mtx)
// {
// 	int	x;
// 	int	y;
// 	int	i;
// 	int	space;

// 	x = 0;
// 	y = 0;
// 	i = 0;
// 	space = 0;
// 	while (mtx[y])
// 	{
// 		while (mtx[y][x])
// 		{
// 		}
// 	}
// }

void	ft_quotes(char **mtx)
{
	int		x;
	int		y;
	t_parse	prs;

	x = 0;
	y = 0;
	prs.len = 0;
	while (mtx[y][x])
	{
		ft_count_quotes(mtx[x], &prs);
		if (prs.sq != 0 || prs.dq != 0)
		{
			while (ft_is_quotes(mtx[x], x))
				x++;
			while (!ft_is_quotes(mtx[x], x))
			{
				x++;
				prs.len++;
			}
			ft_new_str(mtx[x], x - prs.len - 1, prs.len);
			prs.len = 0;
		}
		y++;
	}
}

// void	ft_variables(char **mtx)
// {
// }
