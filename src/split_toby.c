/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_toby.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnegro <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 14:57:46 by mnegro            #+#    #+#             */
/*   Updated: 2023/07/28 14:46:51 by mnegro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_handle_redirects(char *line, t_split *data)
{
	if ((line[data->i] == 60 || line[data->i] == 62) && ft_whether_quotes(data))
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
			while ((line[data->i] == 124 || line[data->i] == 32)
				&& !ft_whether_quotes(data))
				data->i++;
		}
		data->words--;
		return (1);
	}
	return (0);
}

static void	ft_handle_quotes(char *line, t_split *data)
{
	if (line[data->i] == 34 && (data->sq == 0 || data->sq % 2 == 0))
		data->dq++;
	if (line[data->i] == 39 && (data->dq == 0 || data->dq % 2 == 0))
		data->sq++;
	if (!ft_handle_redirects(line, data))
		data->i++;
	while (line[data->i] == 124 && !ft_whether_quotes(data))
		data->i++;
	if (ft_is_stop(line[data->i], 2)
		&& ft_whether_quotes(data))
		data->words++;
}

static int	ft_toby_count(char *line, int i)
{
	t_split	data;

	data.i = i;
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
	return (data.words);
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
