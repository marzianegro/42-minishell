/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnegro <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 18:37:24 by mnegro            #+#    #+#             */
/*   Updated: 2023/08/18 14:39:34 by mnegro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* I cast a void mi servivano solo per vedere se tutto compilava correttamente,
	si possono tranquillamente togliere una volta che si inizia a lavorare
	effettivamente sulle funzioni */
void	ft_clear(t_mini *shell, char **mtx)
{
	(void)shell;
	(void)mtx;
}

void	ft_export(t_mini *shell, char **mtx)
{
	(void)shell;
	(void)mtx;
}

void	ft_env(t_mini *shell)
{
	t_env	*tmp;

	tmp = shell->envp;
	while (tmp && tmp->next)
	{
		if (tmp->value)
			printf("%s\n", tmp->vbl);
		tmp = tmp->next;
	}
}

void	ft_exit(t_mini *shell, char **mtx)
{
	(void)shell;
	(void)mtx;
}

void	ft_vbl(t_mini *shell, char **mtx)
{
	(void)shell;
	(void)mtx;
}
