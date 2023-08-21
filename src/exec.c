/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnegro <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 16:09:33 by mnegro            #+#    #+#             */
/*   Updated: 2023/08/21 15:59:03 by mnegro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_get_token(t_mini *shell, t_token *tkn)
{
	char	*path;
	
}

int	ft_whether_pipe(t_mini *shell)
{
	signal(SIGINT, ft_signal_exec());
	if (shell->tkn && !shell->tkn->next)
	{
		shell->exit_status = ft_exec_red(shell, shell->tkn->red);
		ft_redirects();
		shell->exit_status = ft_exec_toby(shell, shell->tkn->toby);
		return (shell->exit_status);
	}
	else
		return (ft_mini_pipe(shell, shell->tkn));
}
