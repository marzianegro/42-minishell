/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnegro <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 16:10:03 by mnegro            #+#    #+#             */
/*   Updated: 2023/07/27 19:03:39 by mnegro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_parse_line(char *line)
{
	t_mtx	mtx;

	mtx.toby = ft_split_toby(line);
	printf("---------- TOBY ----------\n");
	ft_print_mtx(mtx.toby);
	printf("---------- RED ----------\n");
	mtx.red = ft_split_red(line);
	ft_print_mtx(mtx.red);
}
