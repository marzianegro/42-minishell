/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnegro <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 16:24:58 by mnegro            #+#    #+#             */
/*   Updated: 2023/08/30 17:16:27 by mnegro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_save_exit(t_mini *shell, int n)
{
	static t_mini	*tmp;

	if (shell)
		tmp = shell;
	else
		tmp->exit_status = n;
}

void	ft_signal_handler(int signal)
{
	if (signal == SIGINT)
	{
		ft_save_exit(NULL, 130);
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}
