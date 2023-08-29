/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_red.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnegro <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 17:14:12 by mnegro            #+#    #+#             */
/*   Updated: 2023/08/29 18:27:08 by mnegro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* If -2, no file has been opened, otherwise it means that another
	file is about to be opened and the previous one needs to be closed.
	If -1m there was an error */
// Case: <
int	ft_file_input(t_mini *shell, char *file)
{
	if (!file[0])
	{
		ft_putstr_fd("shell: syntax error near unexpected token `newline'", 2);
		return (1);
	}
	if (!(shell->std_in == -1 || shell->std_in == -2))
		close (shell->std_in);
	shell->std_in = open(file, O_RDONLY);
	if (shell->std_in == -1)
		return (1);
	return (0);
}

/* Open the file in write-only mode,creating if it doesn't exist,
and truncating its content */
// Case: >
int	ft_file_output(t_mini *shell, char *file, int a_or_c)
{
	if (!file[0])
		return (1);
	if (!(shell->std_out == -1 || shell->std_out == -2))
		close (shell->std_out);
	if (a_or_c == 1)
		shell->std_out = open(file, O_WRONLY | O_CREAT | O_APPEND, 0666);
	if (a_or_c == 2)
		shell->std_out = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	return (0);
}

/* Funzione di supporto a ft_exec_red per l'esecuzione dei redirects */
int	ft_exec_red2(t_mini *shell, t_token *tkn, int count)
{
	if (tkn->red[count][0] == '<')
	{
		if (ft_file_input(shell, &tkn->red[count][1]) == 0)
			return (2); /* Ritorna il valore 2, cioe' viene assegnato 2 al valore in caso
				il path dato per l'esecuzione nel caso in cui vada oltre il return 2 dato nella funzione */
	}
	else if (tkn->red[count][0] == '>')
	{
		if (ft_file_output(shell, &tkn->red[count][1], 2) == 0)
		{
			ft_putstr_fd("shell: syntax error near \
				unexpected token `newline'", 2);
			shell->exit_status = 2;
			return (2);
		}
	}
	else if (tkn->red[count][0] == '>' && tkn->red[count][1] == '>')
	{
		if (ft_file_output(shell, &tkn->red[count][1], 1) == 0)
		{
			ft_putstr_fd("shell: syntax error near \
				unexpected token `newline'", 2);
			return (2);
		}
	}
	return (0);
}

/* Funzione che esegue i redirects */
int	ft_exec_red(t_mini *shell, t_token *tkn)
{
	int	count;
	int	exit_code;

	count = 0;
	while (tkn->red && tkn->red[count++])
	{
		if (tkn->red[count][0] == '<' && tkn->red[count][1] == '<')
		{
			if (!tkn->red[count][2])
			{
				ft_putstr_fd("shell: syntax error near \
					unexpected token `newline'", 2);
				shell->exit_status = 2;
				return (2);
			}
			//if (!heredoc)
				return (128 + exit_code); //forse 130 per comando terminato da user
		}
		else
		{
			exit_code = ft_exec_red2(shell, tkn, count);
			if (exit_code)
				return (exit_code);
		}
	}
	return (0);
}
