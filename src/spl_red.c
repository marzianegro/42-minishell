/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spl_red.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnegro <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 15:02:11 by mnegro            #+#    #+#             */
/*   Updated: 2023/09/02 19:14:16 by mnegro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_count_quotes(char *line, t_split *spl)
{
	if (line[spl->i] == '"' && (spl->sq == 0 || spl->sq % 2 == 0))
		spl->dq++;
	if (line[spl->i] == '\'' && (spl->dq == 0 || spl->dq % 2 == 0))
		spl->sq++;
}

static void	ft_handle_redirects(char *line, t_split *spl)
{
	if ((line[spl->i] == '<' || line[spl->i] == '>')
		&& ft_whether_quotes(spl))
	{
		spl->i++;
		if ((line[spl->i - 1] == '<' && line[spl->i] == '<')
			|| (line[spl->i - 1] == '>' && line[spl->i] == '>'))
			spl->i++;
		while (line[spl->i] == ' ')
			spl->i++;
		while (!ft_is_stop(line[spl->i], 1))
		{
			ft_count_quotes(line, spl);
			spl->i++;
			while ((line[spl->i] == '|' || line[spl->i] == ' ')
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
	if ((line[len - 1] == '<' && line[len] == '<')
		|| (line[len - 1] == '>' && line[len] == '>'))
		len++;
	while (line[len] == ' ')
		len++;
	while (line && !ft_is_stop(line[len], 1))
	{
		if (line[len] == '"')
			ft_check_quotes(line, '"', &len);
		else if (line[len] == '\'')
			ft_check_quotes(line, '\'', &len);
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
		if (line[*i] == '"')
			ft_check_quotes(line, '"', i);
		else if (line[*i] == '\'')
			ft_check_quotes(line, '\'', i);
		else if (line[*i] == '<' || line[*i] == '>')
		{
			red[j++] = ft_substr(line, *i, ft_red_length(&line[*i]));
			*i += ft_red_length(&line[*i]);
		}
		else
			*i += 1;
	}
	return (red);
}
