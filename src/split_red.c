/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_red.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnegro <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 15:02:11 by mnegro            #+#    #+#             */
/*   Updated: 2023/07/26 10:32:28 by mnegro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	**ft_split_red(char *line)
{
	char	**red;
	int		i;
	int		j;

	red = (char **)ft_calloc(ft_word_count(line), sizeof(char *));
	if (!red)
		return (NULL);
	i = 0;
	while (line && line[i])
	{
		line[j] = ft_substr(line, i, ft_word_length(line)); 
		j++;
		i += ft_word_length(line);
	}
	line[j] = NULL;
	free((char *)line);
	return (red);
}
