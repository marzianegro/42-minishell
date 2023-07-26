/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnegro <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 15:59:36 by mnegro            #+#    #+#             */
/*   Updated: 2023/07/26 16:26:11 by mnegro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_init_history(t_mini *shell)
{
	char		*history_file;
	int			history_fd;

	history_file = ft_strjoin(getenv("HOME"), "/.mini_history");
	history_fd = open(history_file, O_RDWR | O_CREAT | O_APPEND, 0644);
	// inserire i comandi numerati nel file history_file
}
