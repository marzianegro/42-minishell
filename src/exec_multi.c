/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_multi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnegro <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 11:08:37 by mnegro            #+#    #+#             */
/*   Updated: 2023/08/18 11:22:52 by mnegro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* I cast a void mi servivano solo per vedere se tutto compilava correttamente,
	si possono tranquillamente togliere una volta che si inizia a lavorare
	effettivamente sulle funzioni */

/* In questa funzione ft_exec_red() viene chiamata ricorsivamente usando pipe()
e con tkn->next come parametro */
void	ft_mini_pipe(t_mini *shell, t_token *tkn)
{
	(void)shell;
	(void)tkn;
}
