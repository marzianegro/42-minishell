/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnegro <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 15:51:17 by mnegro            #+#    #+#             */
/*   Updated: 2023/07/28 00:02:51 by mnegro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	main(int argc, char **argv)
{
	t_mini		shell;

	(void)argv;
	if (argc != 1)
	{
		ft_putstr_fd("\033[1;91mError\033[0;39m: invalid input!\n", 2);
		return (1);
	}
	while (1)
	{
		shell.line = readline("minishell-$ ");
		add_history(shell.line);
		ft_parse_line(shell.line);
		free(shell.line);
	}
	return (0);
}
