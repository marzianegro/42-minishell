/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnegro <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 16:10:03 by mnegro            #+#    #+#             */
/*   Updated: 2023/07/26 16:00:41 by mnegro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_parse_line(char *line)
{
	int		i;
	t_rt	rt;
	t_mtx	mtx;

	i = 0;
	while (line && line[i] && line[i] != 124)
	{
		ft_split_toby(line);
		ft_split_red(line);
	}
	ft_lstadd_front(rt, mtx);
}
