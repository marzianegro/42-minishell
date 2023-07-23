/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_all.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnegro <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 16:10:03 by mnegro            #+#    #+#             */
/*   Updated: 2023/07/23 14:51:16 by mnegro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**ft_split(char *str)
{
	char	**mtx;
	int		i;
	int		j;

	mtx = (char **)ft_calloc(ft_word_count(str), sizeof(char *));
	if (!mtx)
		return (NULL);
	i = 0;
	while (str && str[i])
	{
		mtx[j] = ft_substr(str, i, ft_word_length(str)); 
		j++;
		i += ft_word_length(str);
	}
	mtx[j] = NULL;
	free((char *)str);
	return (mtx);
}
