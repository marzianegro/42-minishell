/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnegro <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 18:02:01 by mnegro            #+#    #+#             */
/*   Updated: 2023/08/18 12:07:08 by mnegro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* I cast a void mi servivano solo per vedere se tutto compilava correttamente,
	si possono tranquillamente togliere una volta che si inizia a lavorare
	effettivamente sulle funzioni */
void	ft_cd(t_mini *shell, char **mtx)
{
	(void)shell;
	(void)mtx;
}

void	ft_history(t_mini *shell)
{
	char	*line;
	int		n;

	shell->history_fd = open(shell->history, O_RDONLY);
	line = get_next_line(shell->history_fd);
	n = 0;
	while (line)
	{
		printf("%d  %s", n, line);
		n++;
		free(line);
		line = get_next_line(shell->history_fd);
	}
}

void	ft_echo(char **mtx)
{
	int	y;

	y = 1;
	while (mtx[y])
	{
		if (!ft_strncmp(mtx[1], "-n", 2))
		{
			if (y == 1)
				y++;
			if (!mtx[y + 1])
				printf("%s", mtx[y]);
			else
				printf("%s ", mtx[y]);
			y++;
		}
		else
		{
			if (!mtx[y + 1])
				printf("%s\n", mtx[y]);
			else
				printf("%s ", mtx[y]);
			y++;
		}
	}
}

void	ft_unset(t_mini *shell, char **mtx)
{
	(void)shell;
	(void)mtx;
}

void	ft_pwd(t_mini *shell, char **mtx)
{
	(void)shell;
	(void)mtx;
}
