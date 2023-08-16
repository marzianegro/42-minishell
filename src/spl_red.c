/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spl_red.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnegro <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 15:02:11 by mnegro            #+#    #+#             */
/*   Updated: 2023/08/16 23:32:21 by mnegro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_count_quotes(char *line, t_split *spl)
{
	if (line[spl->i] == 34 && (spl->sq == 0 || spl->sq % 2 == 0))
		spl->dq++;
	if (line[spl->i] == 39 && (spl->dq == 0 || spl->dq % 2 == 0))
		spl->sq++;
}

static void	ft_handle_redirects(char *line, t_split *spl)
{
	if ((line[spl->i] == 60 || line[spl->i] == 62)
		&& ft_whether_quotes(spl))
	{
		spl->i++;
		if ((line[spl->i - 1] == 60 && line[spl->i] == 60)
			|| (line[spl->i - 1] == 62 && line[spl->i] == 62))
			spl->i++;
		while (line[spl->i] == 32)
			spl->i++;
		while (!ft_is_stop(line[spl->i], 1))
		{
			ft_count_quotes(line, spl);
			spl->i++;
			while ((line[spl->i] == 124 || line[spl->i] == 32)
				&& !ft_whether_quotes(spl))
				spl->i++;
		}
		spl->words++;
	}
	else
		spl->i++;
}

static int	ft_red_count(char *line, int i)
{
	t_split	spl;

	spl.i = i;
	spl.dq = 0;
	spl.sq = 0;
	spl.words = 0;
	while (line && !ft_is_stop(line[spl.i], 3))
	{
		ft_count_quotes(line, &spl);
		ft_handle_redirects(line, &spl);
	}
	return (spl.words);
}

static int	ft_red_length(char *line)
{
	int	len;

	len = 1;
	if ((line[len - 1] == 60 && line[len] == 60)
		|| (line[len - 1] == 62 && line[len] == 62))
		len++;
	while (line[len] == 32)
		len++;
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

char	**ft_split_red(char *line, int *i)
{
	char	**red;
	int		j;

	red = (char **)ft_calloc(ft_red_count(line, *i) + 1, sizeof(char *));
	if (!red)
		return (NULL);
	j = 0;
	while (line && !ft_is_stop(line[*i], 3))
	{
		if (line[*i] == 34)
			ft_check_quotes(line, 34, i);
		else if (line[*i] == 39)
			ft_check_quotes(line, 39, i);
		else if (line[*i] == 60 || line[*i] == 62)
		{
			red[j++] = ft_substr(line, *i, ft_red_length(&line[*i]));
			*i += ft_red_length(&line[*i]);
		}
		else
			*i += 1;
	}
	return (red);
}
