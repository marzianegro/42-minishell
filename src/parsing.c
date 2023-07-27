/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnegro <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 16:10:03 by mnegro            #+#    #+#             */
/*   Updated: 2023/07/28 00:02:53 by mnegro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_parse_line(char *line)
{
	t_mtx	mtx;

	mtx.toby = ft_split_toby(line);
	printf("---------- TOBY ----------\n");
	ft_print_mtx(mtx.toby);
	printf("---------- END ----------\n");
	printf("---------- RED ----------\n");
	mtx.red = ft_split_red(line);
	ft_print_mtx(mtx.red);
	printf("---------- END ----------\n");
}


// ERRORI
// ehco ciao >>das"   "das'|' ?Adasd | > dsads 2131 dasdas2
// ehco ciao >>das"   " das
// I due sopra sono stati risolti, i due sotto sono nel calloc, che dovrebbe essere +2 quindi ft_red_count scazza
// cio otpe >" dsa "dsadas' ''"'< dasdas
// cio otpe >" dsa "dsadas' ''"''|' dadsa< dasdas
