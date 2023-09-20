/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnegro <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 16:09:33 by mnegro            #+#    #+#             */
/*   Updated: 2023/09/11 21:20:53 by mnegro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_whether_pipe(t_mini *shell)
{
	signal(SIGINT, ft_handler_exec);
	shell->exit_status = 0;
	if (shell->tkn && !shell->tkn->next)
	{
		ft_exec_red(shell, shell->tkn);
		if (shell->exit_status != 0)
			return (shell->exit_status);
		ft_dup_red(shell, -1, -1);
		shell->exit_status = ft_exec_toby(shell, shell->tkn->toby);
		ft_post_red(shell);
		return (shell->exit_status);
	}
	else
		return (ft_mini_pipe(shell, shell->tkn, 1));
	return (0);
}
