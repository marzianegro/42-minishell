/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseUtils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnegro <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 16:45:37 by mnegro            #+#    #+#             */
/*   Updated: 2023/07/20 17:48:57 by mnegro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_get_wc(char *str)
{
	int	i;
	int	w_count;
	int	flag;

	if (!str)
		return (1);
	i = 0;
	w_count = 0;
	flag = 0;
	while (str && str[i])
	{
		if (str[i] == 32)
			i++;
		else
		{
			if (flag == 0)
				ft_handle_quotes(str);
			if (flag == 1)
			{
				w_count++;
				flag = 0;
			}
		}
	}
	printf("word count: %d", w_count);
	return (w_count);
}

void	ft_handle_quotes(char *str)
{
	int	i;
	int	flag;
	int	q_count;

	i = 0;
	flag = 0;
	q_count = 0;
	while (str && str[i])
	{
		if (str[i] == 34 || str[i] == 39)
			q_count++;
		i++;
		if (q_count != 0 && (str[i] == 32 || str[i] == 124))
			i++;
		if ((q_count == 0 || q_count % 2) && (str[i + 1] == 32 || str[i + 1] == '\0' || str[i + 1] == 124))
		{
			flag = 1;
			i++;
		}
	}
}

int	ft_get_len(char *str)
{
	
}
