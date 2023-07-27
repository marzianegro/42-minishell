/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnegro <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 16:14:13 by mnegro            #+#    #+#             */
/*   Updated: 2023/07/27 12:21:30 by mnegro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_is_stop(int c, int n)
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
			*i += 1;
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
