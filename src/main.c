/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnegro <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 15:51:17 by mnegro            #+#    #+#             */
/*   Updated: 2023/07/15 16:48:03 by mnegro           ###   ########.fr       */
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
		}
		free(shell.input);
	}
	return (0);
}
