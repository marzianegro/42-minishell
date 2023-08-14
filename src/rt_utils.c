/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnegro <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 14:15:34 by mnegro            #+#    #+#             */
/*   Updated: 2023/08/14 12:17:46 by mnegro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_addfront_new(t_rt **rt, char **toby, char **red)
{
	t_rt	*newnode;

	newnode = (t_rt *)ft_calloc(1, sizeof(t_rt));
	if (!newnode)
		return ;
	newnode->toby = toby;
	newnode->red = red;
	newnode->next = NULL;
	if (rt)
	{
		newnode->next = *rt;
		*rt = newnode;
	}
}

void	ft_clear(t_rt **rt)
{
	t_rt	*ptr;

	if (!*rt)
		return ;
	while (*rt)
	{
		ptr = (*rt)->next;
		ft_freematrix((*rt)->toby);
		ft_freematrix((*rt)->red);
		free(*rt);
		*rt = ptr;
	}
	*rt = NULL;
}

void	ft_iter(t_rt *rt, void (*f)(char **))
{
	t_rt	*tmp;

	tmp = rt;
	while (tmp)
	{
		(*f)(rt->red);
		(*f)(rt->toby);
		tmp = tmp->next;
	}
	free(tmp);
}

void	ft_print_rt(t_rt *rt)
{
	printf(" ----- NEW NODE -----\n");
	printf(" --- toby ---\n");
	ft_print_mtx(rt->toby);
	printf(" --- red ---\n");
	ft_print_mtx(rt->red);
	printf("\n");
}
