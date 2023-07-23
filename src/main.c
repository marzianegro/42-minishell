/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnegro <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 15:51:17 by mnegro            #+#    #+#             */
/*   Updated: 2023/07/23 14:51:20 by mnegro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	main(int argc, char **argv)
{
	t_mini	shell;

	(void)argc;
	(void)argv;
	while (1)
	{
		shell.input = readline("minishell-$ ");
		if (shell.input)
		{
			add_history(shell.input);
			ft_parse_input(shell.input);
			ft_exec_input();
		}
		free(shell.input);
	}
	return (0);
}