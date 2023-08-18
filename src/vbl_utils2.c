/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vbl_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnegro <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 14:33:46 by mnegro            #+#    #+#             */
/*   Updated: 2023/08/17 18:32:31 by mnegro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_regular_vbl(char **mtx, t_mini *shell, t_parse *prs)
{
	prs->x++;
	if (ft_is_key(mtx[prs->y][prs->x], 0))
	{
		prs->x++;
		return (1);
	}
	else
	{
		ft_fix_key(&(mtx[prs->y][prs->x]), prs);
		ft_get_key(shell->envp, prs);
		ft_expand(shell->envp, prs);
		prs->x += ft_strlen(prs->key);
	}
}
