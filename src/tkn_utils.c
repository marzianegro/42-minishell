/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tkn_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnegro <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 14:15:34 by mnegro            #+#    #+#             */
/*   Updated: 2023/08/16 17:25:55 by mnegro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_backnew_tkn(t_token **tkn, char **toby, char **red)
{
	t_token	*newnode;
	t_token	*tmp;

	tmp = *tkn;
	while (tmp)
	{
		if (!tmp->next)
			break ;
		tmp = tmp->next;
	}
	newnode = (t_token *)ft_calloc(1, sizeof(t_token));
	if (!newnode)
		return ;
	newnode->toby = toby;
	newnode->red = red;
	newnode->next = NULL;
	if (!*tkn)
		*tkn = newnode;
	else
		tmp->next = newnode;
}

void	ft_clear_tkn(t_token **tkn)
{
	t_token	*ptr;

	if (!*tkn)
		return ;
	while (*tkn)
	{
		ptr = (*tkn)->next;
		ft_freematrix((*tkn)->toby);
		ft_freematrix((*tkn)->red);
		free(*tkn);
		*tkn = ptr;
	}
	*tkn = NULL;
}

void	ft_iter(t_token *tkn, t_mini *shell, void (*f)(char **, t_mini *))
{
	while (tkn)
	{
		(*f)(tkn->toby, shell);
		(*f)(tkn->red, shell);
		tkn = tkn->next;
	}
}

void	ft_print_tkn(t_token *tkn)
{
	printf(" ----- NEW NODE -----\n");
	printf(" --- toby ---\n");
	ft_print_mtx(tkn->toby);
	printf(" --- red ---\n");
	ft_print_mtx(tkn->red);
	printf("\n");
}
