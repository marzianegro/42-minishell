/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_toby.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnegro <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 17:56:23 by mnegro            #+#    #+#             */
/*   Updated: 2023/08/29 15:33:37 by mnegro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_exec_toby(t_mini *shell, char **mtx)
{
	char	*cmd;

	cmd = shell->tkn->toby[0];
	if (!ft_strncmp("cd", cmd, 3))
		ft_cd(shell);
	else if (!ft_strncmp("history", cmd, 8))
		ft_history(shell);
	else if (!ft_strncmp("echo", cmd, 5))
		ft_echo(mtx);
	else if (!ft_strncmp("unset", cmd, 6))
		ft_unset(shell);
	else if (!ft_strncmp("pwd", cmd, 4))
		ft_pwd(shell);
	else if (!ft_strncmp("export", cmd, 7))
		ft_export(shell);
	else if (!ft_strncmp("env", cmd, 4))
		ft_env(shell);
	else if (!ft_strncmp("exit", cmd, 5))
		ft_exit(shell, 0);
	else if (ft_strfind(cmd, '=') && !ft_check_vbl(cmd))
		ft_vbl(shell, cmd, 0);
	else
		ft_exec_binary(shell, cmd);
	return (shell->exit_status);
}
