/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnegro <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 16:09:33 by mnegro            #+#    #+#             */
/*   Updated: 2023/08/18 11:30:15 by mnegro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_exec_line(t_mini *shell)
{
	if (shell->tkn && !shell->tkn->next)
	{
		ft_exec_red(shell, shell->tkn->red);
		ft_exec_toby(shell, shell->tkn->toby);
	}
	else
		ft_mini_pipe(shell, shell->tkn);
}
