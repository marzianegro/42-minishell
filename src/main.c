/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnegro <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 15:51:17 by mnegro            #+#    #+#             */
/*   Updated: 2023/07/20 17:59:01 by mnegro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_handle_quotes(char *str, int *flag, int *i)
{
	int	q_count;

	q_count = 0;
	while (str && str[*i])
	{
		if (str[*i] == 34 || str[*i] == 39)
			q_count++;
		if (q_count != 0 && (str[*i] == 32 || str[*i] == 124))
			*i += 1;
		if (((q_count == 0 || q_count % 2 == 0) && *flag == 0)
			&& (str[*i + 1] == 32 || str[*i + 1] == '\0' || str[*i + 1] == 124))
		{
			*flag = 1;
			return ;
		}
		*i += 1;
	}
}

int	ft_get_wc(char *str)
{
	int	i;
	int	w_count;
	int	flag;

	if (!str)
		return (1);
	i = 0;
	w_count = 0;
	flag = 0;
	while (str && str[i])
	{
		if (str[i] == 32)
			i++;
		else
		{
			if (flag == 0)
				ft_handle_quotes(str, &flag, &i);
			if (flag == 1)
			{
				w_count++;
				flag = 0;
			}
			i++;
		}
	}
	printf("word count: %d\n", w_count);
	printf("i: %d\n", i);
	return (w_count);
}

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
			ft_get_wc(shell.input);
		}
		free(shell.input);
	}
	return (0);
}
