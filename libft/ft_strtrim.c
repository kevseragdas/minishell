/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kagdas <kagdas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 14:19:37 by kagdas            #+#    #+#             */
/*   Updated: 2025/06/25 18:38:07 by kagdas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_end(char *cpy, char const *set)
{
	int	end;
	int	j;
	int	count;

	j = 0;
	count = 0;
	end = ft_strlen(cpy) - 1;
	while (set[j])
	{
		if (cpy[end] == set[j])
		{
			end--;
			count++;
			j = 0;
		}
		else
			j++;
	}
	return (count);
}

static int	ft_start(char *cpy, char const *set)
{
	int	start;
	int	j;

	start = 0;
	j = 0;
	while (set[j])
	{
		if (cpy[start] == set[j])
		{
			start++;
			j = 0;
		}
		else
			j++;
	}
	return (start);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*cpy;
	char	*trim;
	int		start;
	int		end;

	cpy = (char *)s1;
	if (!cpy)
		return (NULL);
	end = ft_end(cpy, set);
	start = ft_start(cpy, set);
	trim = ft_substr(s1, start, (ft_strlen(s1) - end - start));
	if (!trim)
		return (NULL);
	return (trim);
}
