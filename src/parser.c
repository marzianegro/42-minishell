/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnegro <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 16:10:03 by mnegro            #+#    #+#             */
/*   Updated: 2023/08/16 15:50:18 by mnegro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_parse_rt(t_rt **rt)
{
	ft_iter(*rt, ft_parser);
}

void	ft_new_str(char *str, char **new, int start, int len)
{
	char	*tmp;

	tmp = ft_substr(str, start, len);
	*new = ft_strjoin(*new, tmp);
	free(tmp);
}

void	ft_parser(char **mtx, t_mini *shell)
{
	int		x;
	int		y;
	t_parse	prs;

	x = 0;
	y = 0;
	while (mtx[y])
	{
		while (mtx[y][x])
		{
			prs.len = 0;
			if (ft_stoppers(mtx[y], x))
			{
				x++;
				prs.len++;
			}
			ft_handle_stoppers(mtx, x, y, &prs);
		}
		if (prs.new)
			mtx[y] = prs.new;
		y++;
	}
}
