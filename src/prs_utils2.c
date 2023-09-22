/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prs_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnegro <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 14:38:47 by mnegro            #+#    #+#             */
/*   Updated: 2023/09/22 16:30:08 by mnegro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_vbl_cases(char **mtx, t_mini *shell, t_parse *prs)
{
	char	*itoa_exit;

	prs->x++;
	if (mtx[prs->y][prs->x] == '?')
	{
		itoa_exit = ft_itoa(shell->exit_status);
		prs->new = ft_strjoin_gnl(prs->new, itoa_exit);
		free(itoa_exit);
		prs->x++;
	}
	else if (ft_is_key(mtx[prs->y][prs->x], 0))
	{
		prs->new = ft_strjoin_gnl(prs->new, "$");
		return (1);
	}
	else
	{
		ft_fix_key(&(mtx[prs->y][prs->x]), prs);
		ft_get_key(shell->envp, prs);
		ft_expand(shell->envp, prs);
		prs->x += ft_strlen(prs->key);
	}
	return (0);
}

int	ft_variables(char **mtx, t_mini *shell, t_parse *prs)
{
	if (prs->len != 0)
		ft_new_str(mtx[prs->y], prs);
	if (mtx[prs->y][0] == '<' && mtx[prs->y][1] == '<')
	{
		prs->x++;
		prs->len++;
		while (!ft_is_key(mtx[prs->y][prs->x], 1))
		{
			prs->x++;
			prs->len++;
		}
		ft_new_str(mtx[prs->y], prs);
	}
	else
		if (!ft_vbl_cases(mtx, shell, prs))
			return (1);
	return (0);
}
