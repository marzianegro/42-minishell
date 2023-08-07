/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_rt.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnegro <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 16:10:03 by mnegro            #+#    #+#             */
/*   Updated: 2023/08/07 14:22:29 by mnegro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_parse_rt(t_rt **rt)
{
	ft_iter(rt, ft_spaces(rt));
	ft_iter(rt, ft_quotes(rt));
	ft_iter(rt, ft_variables(rt));
}

void	**ft_spaces(t_rt **rt)
{

}

void	**ft_quotes(t_rt **rt)
{

}

void	**ft_variables(t_rt **rt)
{
	
}
