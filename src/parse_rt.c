/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_rt.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnegro <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 16:10:03 by mnegro            #+#    #+#             */
/*   Updated: 2023/08/07 16:16:56 by mnegro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_parse_rt(t_rt **rt)
{
	ft_iter(*rt, ft_spaces);
}

void	ft_spaces(char **mtx)
{
	int	x;
	int	y;
	int	i;
	int	space;

	x = 0;
	y = 0;
	i = 0;
	space = 0;
	while (mtx[y])
	{
		while (mtx[y][x])
		{
			if (mtx[y][x] == 32 && space == 0)
				space = 1;
			else if (mtx[y][x] == 32 && space != 0)
			{
				i = x;
				while (mtx[y][i])
				{
					mtx[y][i] = mtx[y][i + 1];
					i++;
				}
				mtx[y][i] = '\0';
				space = 0;
			}
			x++;
		}
		y++;
		x = 0;
	}
}

// void	ft_quotes(char **mtx)
// {
// }

// void	ft_variables(char **mtx)
// {
// }
