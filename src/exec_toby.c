/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_toby.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnegro <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 17:56:23 by mnegro            #+#    #+#             */
/*   Updated: 2023/08/18 11:11:46 by mnegro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_exec_toby(t_mini *shell, char **mtx)
{
	char	*cmd;

	cmd = shell->tkn->toby[0];
	if (!ft_strncmp("cd", cmd, 3))
		ft_cd();
	else if (!ft_strncmp("history", cmd, 8))
		ft_history();
	else if (!ft_strncmp("echo", cmd, 5))
		ft_echo();
	else if (!ft_strncmp("unset", cmd, 6))
		ft_unset();
	else if (!ft_strncmp("pwd", cmd, 4))
		ft_pwd();
	else if (!ft_strncmp("clear", cmd, 6))
		ft_clear();
	else if (!ft_strncmp("export", cmd, 7))
		ft_export();
	else if (!ft_strncmp("env", cmd, 4))
		ft_env();
	else if (!ft_strncmp("exit", cmd, 5))
		ft_exit();
	else if (!ft_strncmp("KEY=value", cmd, 10))
		ft_vbl();
	else
		ft_binary(shell);
}

void	ft_binary(t_mini *shell)
{}
