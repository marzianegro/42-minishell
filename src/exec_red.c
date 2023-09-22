/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_red.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnegro <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 17:14:12 by mnegro            #+#    #+#             */
/*   Updated: 2023/09/22 16:29:11 by mnegro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_exec_red(t_mini *shell, t_token *tkn)
{
	int	y;

	y = 0;
	while (tkn->red && tkn->red[y])
	{
		if (ft_red_in(shell, tkn, y))
			break ;
		else if (ft_red_out(shell, tkn, y))
			break ;
		y++;
	}
}

int	ft_red_in(t_mini *shell, t_token *tkn, int y)
{
	if (tkn->red[y][0] == '<' && tkn->red[y][1] != '<')
		ft_file_input(shell, &tkn->red[y][1]);
	else if (tkn->red[y][0] == '<' && tkn->red[y][1] == '<')
	{
		if (!tkn->red[y][2])
		{
			ft_putstr_fd("perroshell: syntax error near "
				"unexpected token `newline'\n", 2);
			shell->exit_status = 2;
		}
		else
			ft_handle_here_doc(shell, &tkn->red[y][2]);
	}
	return (shell->exit_status);
}

int	ft_red_out(t_mini *shell, t_token *tkn, int y)
{
	if (tkn->red[y][0] == '>' && tkn->red[y][1] != '>')
		ft_file_output(shell, &tkn->red[y][1], 2);
	else if (tkn->red[y][0] == '>' && tkn->red[y][1] == '>')
	{
		if (ft_file_output(shell, &tkn->red[y][2], 1))
		{
			ft_putstr_fd("perroshell: syntax error near "
				"unexpected token `newline'\n", 2);
			shell->exit_status = 2;
		}
	}
	return (shell->exit_status);
}
