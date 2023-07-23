/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnegro <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 15:59:36 by mnegro            #+#    #+#             */
/*   Updated: 2023/07/23 16:59:28 by mnegro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_init_history(t_mini *shell)
{
	char		*history_file;
	int			history_fd;

	history_file = ft_strjoin(getenv("HOME"), "/.mini_history");
	history_fd = open(history_file, O_RDWR | O_CREAT | O_APPEND, 0644);
	ft_putstr_fd(shell->input, history_fd);
}
