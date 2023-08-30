/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnegro <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 16:09:33 by mnegro            #+#    #+#             */
/*   Updated: 2023/08/30 17:03:40 by mnegro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_whether_pipe(t_mini *shell)
{
	if (shell->tkn && !shell->tkn->next)
	{
		shell->exit_status = ft_exec_red(shell, shell->tkn);
		if (shell->exit_status)
			return (shell->exit_status);
		ft_dup(shell, -1, -1);
		shell->exit_status = ft_exec_toby(shell, shell->tkn->toby);
		return (shell->exit_status);
	}
	else
		return (ft_mini_pipe(shell, shell->tkn));
	return (0);
}
