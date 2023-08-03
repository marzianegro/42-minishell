/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnegro <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 15:59:36 by mnegro            #+#    #+#             */
/*   Updated: 2023/08/03 17:33:14 by mnegro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_init_history(t_mini *shell)
{
	char	*line;

	shell->history = ft_strjoin(getenv("HOME"), "/.mini_history");
	shell->history_fd = open(shell->history, O_RDWR | O_CREAT, 0644);
	line = get_next_line(shell->history_fd);
	if (!line)
		return ;
	else
	{
		while (line)
		{
			line[ft_strlen(line) - 1] = 0;
			add_history(line);
			free(line);
			line = get_next_line(shell->history_fd);
		}
	}
}
