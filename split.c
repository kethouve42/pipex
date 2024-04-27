/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kethouve <kethouve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 17:40:10 by kethouve          #+#    #+#             */
/*   Updated: 2024/03/13 16:16:41 by kethouve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*put_words(char const *s, int debut, int end, int env)
{
	int		i;
	char	*word;

	i = 0;
	if (env == 1)
		word = malloc(((end - debut) + 2) * sizeof(char));
	else
		word = malloc(((end - debut) + 1) * sizeof(char));
	if (!word)
		return (0);
	while (debut < end)
	{
		word[i] = s[debut];
		i++;
		debut++;
	}
	if (env == 1)
		word[i++] = '/';
	word[i] = '\0';
	return (word);
}

int	tabs_size(char const *s, char c, int env)
{
	int	i;
	int	count;
	int	j;

	if (env == 1)
		i = 5;
	else
		i = 0;
	count = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] != c && count == 0)
		{
			count = 1;
			j++;
		}
		else if (s[i] == c)
			count = 0;
		i++;
	}
	return (j);
}

char	**ft_split(char const *s, char c, int env, int i)
{
	int		j;
	int		index;
	char	**dest;

	j = 0;
	index = -1;
	dest = malloc((tabs_size(s, c, env) + 1) * sizeof(char *));
	if (!s || !dest)
		return (0);
	while (i <= ft_strlen(s))
	{
		if (s[i] != c && index < 0)
			index = i;
		else if ((s[i] == c || i == ft_strlen(s)) && index >= 0)
		{
			dest[j++] = put_words(s, index, i, env);
			index = -1;
		}
		i++;
	}
	dest[j] = NULL;
	return (dest);
}
