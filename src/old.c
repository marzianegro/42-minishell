/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   old.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnegro <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 16:45:37 by mnegro            #+#    #+#             */
/*   Updated: 2023/07/23 14:51:19 by mnegro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_count_quotes(char *str)
{
	int	i;
	int	quotes;

	i = 0;
	quotes = 0;
	while (str && str[i])
	{
		if (str[i] == 34 || str[i] == 39)
			quotes++;
		i++;
	}
	return (quotes);
}

int	ft_handle_quotes(char *str, int *i)
{
	int	quotes;
	int	q_count;

	quotes = ft_count_quotes(str);
	q_count = 0;
	while (str && str[*i])
	{
		if (str[*i] == 34 || str[*i] == 39)
			q_count++;
		if (q_count != 0 && (str[*i] == 32 || str[*i] == 124))
		{
			*i += 1;
			continue ;
		}
		if ((q_count == 0 || q_count == quotes)
			&& (str[*i + 1] == 0 || str[*i + 1] == 32 || str[*i + 1] == 124))
			return (1);
		*i += 1;
	}
	return (0);
}

int	ft_get_wc(char *str)
{
	int	i;
	int	w_count;

	if (!str)
		return (1);
	i = 0;
	w_count = 0;
	while (str && str[i])
	{
		if (str[i] == 32)
			i++;
		else
		{
			if (ft_handle_quotes(str, &i))
				w_count++;
			i++;
		}
	}
	return (w_count);
}

int	ft_get_len(char *str)
{
	
}
