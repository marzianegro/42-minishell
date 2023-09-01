/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_red.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnegro <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 17:14:12 by mnegro            #+#    #+#             */
/*   Updated: 2023/09/01 16:44:14 by mnegro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_exec_red(t_mini *shell, t_token *tkn)
{
	int	y;

	y = 0;
	while (tkn->red && tkn->red[y])
	{
		if (ft_red_in(shell, tkn, y) == 2)
			return (1);
		else if (ft_red_out(shell, tkn, y) == 2)
			return (1);
		y++;
	}
	return (0);
}

/* Con return (2) viene assegnato 2 al valore in caso il path dato per
	l'esecuzione nel caso in cui vada oltre il return (2) dato nella funzione */
int	ft_red_in(t_mini *shell, t_token *tkn, int y)
{
	if (tkn->red[y][0] == '<') // aggiungere controllo su [y][1]
	{
		if (ft_file_input(shell, &tkn->red[y][1]) == 0)
		{
			shell->exit_status = 2;
			return (2);
		}
	}
	else if (tkn->red[y][0] == '<' && tkn->red[y][1] == '<')
	{
		if (!tkn->red[y][2])
		{
			ft_putstr_fd("shell: syntax error near "
				"unexpected token `newline'\n", 2);
			shell->exit_status = 2;
			return (shell->exit_status);
		}
		// if (!ft_here_doc_parent(shell, &tkn->red[i][2]))
		// 	return (128 + shell->exit_status); //forse 130 per comando terminato da user
	}
	return (0);
}

int	ft_red_out(t_mini *shell, t_token *tkn, int y)
{
	if (tkn->red[y][0] == '>' && tkn->red[y][1] != '>')
	{
		if (ft_file_output(shell, &tkn->red[y][1], 2) == 1)
		{
			ft_putstr_fd("shell: syntax error near "
				"unexpected token `newline'\n", 2);
			shell->exit_status = 2;
			return (2);
		}
	}
	else if (tkn->red[y][0] == '>' && tkn->red[y][1] == '>')
	{
		if (ft_file_output(shell, &tkn->red[y][1], 1) == 1)
		{
			ft_putstr_fd("shell: syntax error near "
				"unexpected token `newline'\n", 2);
			shell->exit_status = 2;
			return (2);
		}
	}
	return (0);
}
