/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnegro <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 16:14:13 by mnegro            #+#    #+#             */
/*   Updated: 2023/07/28 00:03:01 by mnegro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_is_stop(char c, int n)
{
	if (n == 1)
	{
		if (c == 0 || c == 32 || c == 60 || c == 62 || c == 124)
			return (1);
	}
	else if (n == 2)
	{
		if (c == 0 || c == 32 || c == 124)
			return (1);
	}
	else if (n == 3)
	{
		if (c == 0 || c == 124)
			return (1);
	}
	return (0);
}

int	ft_whether_quotes(t_split *data)
{
	if ((data->sq == 0 || data->sq % 2 == 0)
		&& (data->dq == 0 || data->dq % 2 == 0))
		return (1);
	return (0);
}

void	ft_check_quotes(char *str, char c, int *len)
{
	*len += 1;
	while (str[*len] != c)
		*len += 1;
	*len += 1;
}

void	ft_check_redirects(char *str, int *i)
{
	while (str[*i] == 60 || str[*i] == 62)
	{
		*i += 1;
		if ((str[*i - 1] == 60 && str[*i] == 60)
			|| (str[*i - 1] == 62 && str[*i] == 62))
			*i += 1;
		if (str[*i] == 32)
			*i += 1;
		while (!ft_is_stop(str[*i], 1))
		{
			if (str[*i] == 34)
				ft_check_quotes(str, 34, i);
			else if (str[*i] == 39)
				ft_check_quotes(str, 39, i);
			else
				*i += 1;
		}
	}
}

void	ft_print_mtx(char **mtx)
{
	int	i;

	i = 0;
	while (mtx[i])
	{
		printf("%s\n", mtx[i]);
		i++;
	}
}
