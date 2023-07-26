/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_toby.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnegro <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 14:57:46 by mnegro            #+#    #+#             */
/*   Updated: 2023/07/26 16:25:12 by mnegro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_handle_redirects(char *line, t_split *data)
{
	if ((line[data->i] == 60 || line[data->i] == 62)
		&& (data->sq == 0 || data->sq % 2 == 0)
		&& (data->dq == 0 || data->dq % 2 == 0))
	{
		if (data->i != 0 && line[data->i - 1] != 32)
			data->words++;
		data->i++;
		if ((line[data->i - 1] == 60 && line[data->i] == 60)
			|| (line[data->i - 1] == 62 && line[data->i] == 62))
			data->i++;
		while (line[data->i] == 32)
			data->i++;
		while (!ft_is_stop(line[data->i], 1))
		{
			if (line[data->i] == 34 && (data->sq == 0 || data->sq % 2 == 0))
				data->dq++;
			if (line[data->i] == 39 && (data->dq == 0 || data->dq % 2 == 0))
				data->sq++;
			data->i++;
		}
		data->words--;
		return (1);
	}
	return (0);
}

void	ft_handle_quotes(char *line, t_split *data)
{
	if (line[data->i] == 34 && (data->sq == 0 || data->sq % 2 == 0))
		data->dq++;
	if (line[data->i] == 39 && (data->dq == 0 || data->dq % 2 == 0))
		data->sq++;
	if (!ft_handle_redirects(line, data))
		data->i++;
	if (ft_is_stop(line[data->i], 2)
		&& (data->dq == 0 || data->dq % 2 == 0)
		&& (data->sq == 0 || data->sq % 2 == 0))
		data->words++;
}

int	ft_word_count(char *line)
{
	t_split	data;

	data.i = 0;
	data.dq = 0;
	data.sq = 0;
	data.words = 0;
	while (line && !ft_is_stop(line[data.i], 3))
	{
		if (line[data.i] == 32)
			data.i++;
		else
			ft_handle_quotes(line, &data);
	}
	if (data.dq % 2 || data.sq % 2)
		while (1)
			readline("> ");
	printf("Word count: %d\n", data.words);
	return (data.words);
}

int	ft_word_length(char *line)
{
}

char	**ft_split_toby(char *line)
{
	char	**toby;
	int		i;
	int		j;

	toby = (char **)ft_calloc(ft_word_count(line), sizeof(char *));
	if (!toby)
		return (NULL);
	i = 0;
	j = 0;
	while (line && line[i])
	{
		line[j] = ft_substr(line, i, ft_word_length(line)); 
		j++;
		i += ft_word_length(line);
	}
	line[j] = NULL;
	free((char *)line);
	return (toby);
}
