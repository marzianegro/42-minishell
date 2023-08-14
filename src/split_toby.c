/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_toby.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnegro <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 14:57:46 by mnegro            #+#    #+#             */
/*   Updated: 2023/08/14 12:15:52 by mnegro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_handle_redirects(char *line, t_split *spl)
{
	if ((line[spl->i] == 60 || line[spl->i] == 62) && ft_whether_quotes(spl))
	{
		if (spl->i != 0 && line[spl->i - 1] != 32)
			spl->words++;
		spl->i++;
		if ((line[spl->i - 1] == 60 && line[spl->i] == 60)
			|| (line[spl->i - 1] == 62 && line[spl->i] == 62))
			spl->i++;
		while (line[spl->i] == 32)
			spl->i++;
		while (!ft_is_stop(line[spl->i], 1))
		{
			if (line[spl->i] == 34 && (spl->sq == 0 || spl->sq % 2 == 0))
				spl->dq++;
			if (line[spl->i] == 39 && (spl->dq == 0 || spl->dq % 2 == 0))
				spl->sq++;
			spl->i++;
			while ((line[spl->i] == 124 || line[spl->i] == 32)
				&& !ft_whether_quotes(spl))
				spl->i++;
		}
		spl->words--;
		return (1);
	}
	return (0);
}

static void	ft_handle_quotes(char *line, t_split *spl)
{
	if (line[spl->i] == 34 && (spl->sq == 0 || spl->sq % 2 == 0))
		spl->dq++;
	if (line[spl->i] == 39 && (spl->dq == 0 || spl->dq % 2 == 0))
		spl->sq++;
	if (!ft_handle_redirects(line, spl))
		spl->i++;
	while (line[spl->i] == 124 && !ft_whether_quotes(spl))
		spl->i++;
	if (ft_is_stop(line[spl->i], 2)
		&& ft_whether_quotes(spl))
		spl->words++;
}

static int	ft_toby_count(char *line, int i)
{
	t_split	spl;

	spl.i = i;
	spl.dq = 0;
	spl.sq = 0;
	spl.words = 0;
	while (line && !ft_is_stop(line[spl.i], 3))
	{
		if (line[spl.i] == 32)
			spl.i++;
		else
			ft_handle_quotes(line, &spl);
	}
	if (spl.dq % 2 || spl.sq % 2)
		while (1)
			readline("> ");
	return (spl.words);
}

static int	ft_toby_length(char *line)
{
	int	len;

	len = 0;
	while (line && !ft_is_stop(line[len], 1))
	{
		if (line[len] == 34)
			ft_check_quotes(line, 34, &len);
		else if (line[len] == 39)
			ft_check_quotes(line, 39, &len);
		else
			len++;
	}
	return (len);
}

char	**ft_split_toby(char *line, int i)
{
	char	**toby;
	int		j;

	toby = (char **)ft_calloc(ft_toby_count(line, i) + 1, sizeof(char *));
	if (!toby)
		return (NULL);
	j = 0;
	while (line && !ft_is_stop(line[i], 3))
	{
		if (line[i] == 32)
			i++;
		else if (line[i] == 60 || line[i] == 62)
			ft_check_redirects(line, &i);
		else
		{
			toby[j++] = ft_substr(line, i, ft_toby_length(&line[i])); 
			i += ft_toby_length(&line[i]);
		}
	}
	return (toby);
}
