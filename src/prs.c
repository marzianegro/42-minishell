/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnegro <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 16:10:03 by mnegro            #+#    #+#             */
/*   Updated: 2023/08/16 20:19:32 by mnegro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_parse_token(t_token **tkn, t_mini *shell)
{
	ft_iter(*tkn, shell, ft_parser);
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
	t_parse	prs;

	prs.y = 0;
	while (mtx[prs.y])
	{
		prs.x = 0;
		prs.new = NULL;
		prs.len = 0;
		while (mtx[prs.y][prs.x])
		{
			if (!ft_stoppers(mtx[prs.y][prs.x]))
			{
				prs.x++;
				prs.len++;
			}
			if (ft_handle_stoppers(mtx, shell, &prs))
				continue ;
		}
		if (prs.new)
		{
			free(mtx[prs.y]);
			mtx[prs.y] = prs.new;
		}
		prs.y++;
	}
}
