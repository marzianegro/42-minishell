/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prs_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnegro <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 15:37:32 by mnegro            #+#    #+#             */
/*   Updated: 2023/08/16 18:23:48 by mnegro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_stoppers(char c)
{
	if (c == '"' || c == '$' || c == '\'')
		return (1);
	return (0);
}

int	ft_handle_stoppers(char **mtx, t_mini *shell, t_parse *prs)
{
	if (!ft_stoppers(mtx[prs->y][prs->x]))
	{
		if (prs->len != 0)
		{
			ft_new_str(mtx[prs->y], &prs->new, prs->x - prs->len, prs->len);
			prs->len = 0;
		}
		if (mtx[prs->y][prs->x] == '\'')
			ft_single_quotes(mtx, prs);
		else if (mtx[prs->y][prs->x] == '"')
			ft_double_quotes(mtx, shell, prs);
		else if (mtx[prs->y][prs->x] == '$')
			if (!ft_variables(mtx, shell, prs))
				return (1);
	}
	return (0);
}

void	ft_single_quotes(char **mtx, t_parse *prs)
{
	prs->x++;
	while (mtx[prs->y][prs->x] != '\'')
	{
		prs->x++;
		prs->len++;
	}
	ft_new_str(mtx[prs->y], &prs->new, prs->x - prs->len, prs->len);
	prs->x++;
}

void	ft_double_quotes(char **mtx, t_mini *shell, t_parse *prs)
{
	prs->x++;
	while (mtx[prs->y][prs->x] != '"')
	{
		if (mtx[prs->y][prs->x] == '$')
		{
			prs->x++;
			if (!ft_is_key(mtx[prs->y][prs->x], 0))
				prs->x++;
			else
			{
				ft_fix_key(&(mtx[prs->y][prs->x]), prs);
				ft_get_key(shell->envp, prs);
				ft_expand(shell->envp, prs);
				prs->x += ft_strlen(prs->key);
			}
		}
		prs->x++;
		prs->len++;
	}
	ft_new_str(mtx[prs->y], &prs->new, prs->x - prs->len, prs->len);
}

// con cosa sostituisco continue?
int	ft_variables(char **mtx, t_mini *shell, t_parse *prs)
{
	prs->x++;
	if (!ft_is_key(mtx[prs->y][prs->x], 0))
	{
		prs->x++;
		return (1);
	}
	else
	{
		ft_get_key(shell->envp, prs);
		ft_expand(shell->envp, prs);
	}
	return (0);
}
