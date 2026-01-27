/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kagdas <kagdas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 14:43:07 by kagdas            #+#    #+#             */
/*   Updated: 2025/06/25 18:38:11 by kagdas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_word_long(char const *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static int	ft_word_count(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i])
			count++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (count);
}

static char	**ft_free(char **new, int j)
{
	while (new[j])
	{
		free(new[j]);
		j--;
	}
	free(new);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**new;
	size_t	i;
	int		j;

	new = malloc(sizeof(char *) * (ft_word_count(s, c) + 1));
	if (!new)
		return (NULL);
	i = 0;
	j = 0;
	while (i < ft_strlen(s))
	{
		while (s[i] == c)
			i++;
		if (s[i])
		{
			new[j] = ft_substr(s, i, ft_word_long(s + i, c));
			if (!new[j])
				return (ft_free(new, j));
			i = i + ft_word_long(s + i, c);
			j++;
		}
	}
	new[j] = NULL;
	return (new);
}
