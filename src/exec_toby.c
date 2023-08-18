/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_toby.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnegro <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 17:56:23 by mnegro            #+#    #+#             */
/*   Updated: 2023/08/18 14:31:10 by mnegro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_exec_toby(t_mini *shell, char **mtx)
{
	char	*cmd;

	cmd = shell->tkn->toby[0];
	if (!ft_strncmp("cd", cmd, 3))
		ft_cd(shell, mtx);
	else if (!ft_strncmp("history", cmd, 8)) // optional
		ft_history(shell);
	else if (!ft_strncmp("echo", cmd, 5))
		ft_echo(mtx);
	else if (!ft_strncmp("unset", cmd, 6))
		ft_unset(shell, mtx);
	else if (!ft_strncmp("pwd", cmd, 4))
		ft_pwd(shell, mtx);
	else if (!ft_strncmp("clear", cmd, 6)) // optional
		ft_clear(shell, mtx);
	else if (!ft_strncmp("export", cmd, 7))
		ft_export(shell, mtx);
	else if (!ft_strncmp("env", cmd, 4))
		ft_env(shell);
	else if (!ft_strncmp("exit", cmd, 5))
		ft_exit(shell, mtx);
	else if (!ft_strncmp("KEY=value", cmd, 10)) // optional
		ft_vbl(shell, mtx);
	else
		ft_binary(shell);
}

/* Il cast a void mi serviva solo per vedere se tutto compilava correttamente,
	si può tranquillamente togliere una volta che si inizia a lavorare
	effettivamente sulla funzione */
void	ft_binary(t_mini *shell)
{
	(void)shell;
}
