/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnegro <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 16:14:13 by mnegro            #+#    #+#             */
/*   Updated: 2023/07/26 16:25:15 by mnegro           ###   ########.fr       */
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
