 /* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnegro <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 16:10:03 by mnegro            #+#    #+#             */
/*   Updated: 2023/09/02 19:14:13 by mnegro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_parser(char **mtx, t_mini *shell)
{
	t_parse	prs;

	prs.y = 0;
	while (mtx[prs.y])
	{
		prs.x = 0;
		prs.new = NULL;
		prs.len = 0;
		while (mtx[prs.y][prs.x])
		{
			if (ft_parser_red(mtx, &prs))
				continue ;
			if (!ft_stoppers(mtx[prs.y][prs.x]))
			{
				prs.x++;
				prs.len++;
			}
			if (ft_handle_stoppers(mtx, shell, &prs))
				continue ;
		}
		free(mtx[prs.y]);
		mtx[prs.y] = prs.new;
		prs.y++;
	}
}

int	ft_parser_red(char **mtx, t_parse *prs)
{
	if (mtx[prs->y][prs->x] == '>' || mtx[prs->y][prs->x] == '<')
	{
		prs->x++;
		prs->len++;
		if ((mtx[prs->y][prs->x] == '>' && mtx[prs->y][prs->x - 1] == '>')
			|| (mtx[prs->y][prs->x] == '<' && mtx[prs->y][prs->x - 1] == '<'))
		{
			prs->x++;
			prs->len++;
		}
		ft_new_str(mtx[prs->y], prs);
		if (mtx[prs->y][prs->x] == ' ')
		{
			while (mtx[prs->y][prs->x] == ' ')
				prs->x++;
			return (1);
		}
	}
	return (0);
}

void	ft_parse_token(t_token **tkn, t_mini *shell)
{
	ft_iter(*tkn, shell, ft_parser);
}
