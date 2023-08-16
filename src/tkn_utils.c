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

void	ft_addfront_new(t_token **tkn, char **toby, char **red)
{
	t_token	*newnode;

	newnode = (t_token *)ft_calloc(1, sizeof(t_token));
	if (!newnode)
		return ;
	newnode->toby = toby;
	newnode->red = red;
	newnode->next = NULL;
	if (tkn)
	{
		newnode->next = *tkn;
		*tkn = newnode;
	}
}

void	ft_clear(t_token **tkn)
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
	t_token	*tmp;

	tmp = tkn;
	while (tmp)
	{
		(*f)(tkn->toby, shell);
		(*f)(tkn->red, shell);
		tmp = tmp->next;
	}
	free(tmp);
}

void	ft_print_token(t_token *tkn)
{
	printf(" ----- NEW NODE -----\n");
	printf(" --- toby ---\n");
	ft_print_mtx(tkn->toby);
	printf(" --- red ---\n");
	ft_print_mtx(tkn->red);
	printf("\n");
}
