/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_red.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnegro <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 17:55:47 by mnegro            #+#    #+#             */
/*   Updated: 2023/08/21 15:53:47 by mnegro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
/*
-if -2 then no file has been opened otherwise it means,
 another file is about to be opened and we need to close 
 the previous one
-if -1 ther was an error*/
// <
int	ft_file_input(t_mini *shell, char *file)
{
	if (!file[0])
	{
		ft_putstr_fd("shell: syntax error near unexpected token `newline'", 2);
		return (1);
	}
	if (!(shell->fd_input == -1 && shell->fd_input == -2))
		close (shell->fd_input);
	shell->fd_input = open(file, O_RDONLY);
	if (shell->fd_input == -1)
	{
		perror(file);
		return (1);
	}
	return (0);
}

/*//
Open the file in write-only mode,creating if it doesn't exist,
and truncating its content
 */
// >
int	ft_file_output(t_mini *shell, char *file, int a_or_c)
{
	if (!file[0])
		return (1);
	if (!(shell->fd_output == -1 && shell->fd_output == -2))
		close (shell->fd_output);
	if (a_or_c == 1)
		shell->fd_output = open (file, O_WRONLY | O_CREAT | O_APPEND, 0666);
	if (a_or_c == 2)
		shell->fd_output = open (file, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	return (0);
}

/*funzione di supporto a exec_red per l'esecuzione dei redirects*/
int	ft_exec_red2(t_mini *shell, t_token *tkn, int count)
{
	if (tkn->red[count][0] == '<')
	{
		if (ft_file_input(shell, &tkn->red[count][1]) == 0)
			return (2); //ritorna il valore 2, cioe' viene assegnato 2 al valore in caso il path dato  per l'esecuzione nel caso in cui vada oltre il return 2 dato nella funzione.
	}
	else if (tkn->red[count][0] == '>')
	{
		if (ft_file_output(shell, &tkn->red[count][1], 2) == 0)
		{
			ft_putstr_fd("shell: syntax error near unexpected token `newline'", 2);
			return (2);
		}
	}
	else if (tkn->red[count][0] = '>' && tkn->red[count][1] == '>')
	{
		if (ft_file_output(shell, &tkn->red[count][1], 1) == 0)
		{
			ft_putstr_fd("shell: syntax error near unexpected token `newline'", 2);
			return (2);
		}
	}
	return (0);
}

/*funzione che esegue i redirects*/
int	ft_exec_red(t_mini *shell, t_token *tkn)
{
	int	count;
	int	exitcode;
	
	count = 0;
	while (tkn->red && tkn->red[count++])
	{
		if (tkn->red[count][0] == '<' && tkn->red[count][1] == '<')
		{
			if(!tkn->red[count][2])
				ft_error_with_red(shell);
				return (1);
			//if (!heredoc)
				return (128 + exitcode); //forse 130 per comando terminato da user
		}
		else
		{
			exitcode = ft_exec_red2(shell, tkn, count);
			if (exitcode)
				return (exitcode);
		}
	}
	return (0);
}
