/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnegro <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 14:11:24 by mnegro            #+#    #+#             */
/*   Updated: 2023/08/16 23:32:39 by mnegro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_freematrix(char **matrix)
{
	int	i;

	i = 0;
	if (matrix)
	{
		while (matrix[i])
		{
			free(matrix[i]);
			i++;
		}
		free(matrix);
	}
}

void	ft_print_mtx(char **mtx)
{
	int	y;

	y = 0;
	while (mtx[y] != NULL)
	{
		printf("%s\n", mtx[y]);
		y++;
	}
}

void	ft_putstr_fd_ms(char *s, int fd)
{
	int	i;

	i = 0;
	if (fd < 0 || s[i] == '\n')
		return ;
	while (s[i] != '\0')
	{
		write(fd, &s[i], 1);
		i++;
	}
	write(fd, "\n", 1);
}
