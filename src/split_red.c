/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_red.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnegro <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 15:02:11 by mnegro            #+#    #+#             */
/*   Updated: 2023/08/10 11:10:36 by mnegro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_count_quotes(char *line, t_split *data)
{
	if (line[data->i] == 34 && (data->sq == 0 || data->sq % 2 == 0))
		data->dq++;
	if (line[data->i] == 39 && (data->dq == 0 || data->dq % 2 == 0))
		data->sq++;
}

static void	ft_handle_redirects(char *line, t_split *data)
{
	if ((line[data->i] == 60 || line[data->i] == 62)
		&& ft_whether_quotes(data))
	{
		data->i++;
		if ((line[data->i - 1] == 60 && line[data->i] == 60)
			|| (line[data->i - 1] == 62 && line[data->i] == 62))
			data->i++;
		if (line[data->i] == 32)
			data->i++;
		while (!ft_is_stop(line[data->i], 1))
		{
			ft_count_quotes(line, data);
			data->i++;
			while ((line[data->i] == 124 || line[data->i] == 32)
				&& !ft_whether_quotes(data))
				data->i++;
		}
		data->words++;
	}
	else
		data->i++;
}

static int	ft_red_count(char *line, int i)
{
	t_split	data;

	data.i = i;
	data.dq = 0;
	data.sq = 0;
	data.words = 0;
	while (line && !ft_is_stop(line[data.i], 3))
	{
		ft_count_quotes(line, &data);
		ft_handle_redirects(line, &data);
	}
	return (data.words);
}

static int	ft_red_length(char *line)
{
	int	len;

	len = 1;
	if ((line[len - 1] == 60 && line[len] == 60)
		|| (line[len - 1] == 62 && line[len] == 62))
		len++;
	if (line[len] == 32)
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
