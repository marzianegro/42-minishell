/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnegro <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 16:09:33 by mnegro            #+#    #+#             */
/*   Updated: 2023/08/18 10:48:01 by mnegro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_exec_line(t_mini *shell)
{
	se sei al primo nodo e next = NULL
	{
		ft_exec_red(shell);
		ft_exec_toby(shell);
	}
	else
		ft_mini_pipe();
			chiamare ricorsivamente ft_exec_red(), usando pipe(), con tkn->next come argomento
}

void	ft_binary()
{}
