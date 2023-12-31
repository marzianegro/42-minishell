/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spl_toby.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnegro <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 14:57:46 by mnegro            #+#    #+#             */
/*   Updated: 2023/09/22 16:30:50 by mnegro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_handle_redirects(char *line, t_split *spl)
{
	if ((line[spl->i] == '<' || line[spl->i] == '>') && ft_whether_quotes(spl))
	{
		if (spl->i != '\0' && line[spl->i - 1] != ' ')
			spl->words++;
		spl->i++;
		if ((line[spl->i - 1] == '<' && line[spl->i] == '<')
			|| (line[spl->i - 1] == '>' && line[spl->i] == '>'))
			spl->i++;
		while (line[spl->i] == ' ')
		{
			spl->i++;
			if (line[spl->i] == '<' || line[spl->i] == '>')
			{
				spl->words++;
				spl->i++;
			}
		}
		while (!ft_is_stop(line[spl->i], 1))
			ft_regular_red(line, spl);
		spl->words--;
		return (1);
	}
	return (0);
}

static void	ft_handle_quotes(char *line, t_split *spl)
{
	if (line[spl->i] == '"' && (spl->sq == 0 || spl->sq % 2 == 0))
		spl->dq++;
	if (line[spl->i] == '\'' && (spl->dq == 0 || spl->dq % 2 == 0))
		spl->sq++;
	if (!ft_handle_redirects(line, spl))
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
		if (line[spl.i] == ' ')
			spl.i++;
		else
			ft_handle_quotes(line, &spl);
		while (line[spl.i] == '|' && !ft_whether_quotes(&spl))
			spl.i++;
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
		if (line[len] == '"')
			ft_check_quotes(line, '"', &len);
		else if (line[len] == '\'')
			ft_check_quotes(line, '\'', &len);
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
		if (line[i] == ' ')
			i++;
		else if (line[i] == '<' || line[i] == '>')
			ft_check_redirects(line, &i);
		else
		{
			toby[j++] = ft_substr(line, i, ft_toby_length(&line[i])); 
			i += ft_toby_length(&line[i]);
		}
	}
	return (toby);
}
