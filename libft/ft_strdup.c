/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kagdas <kagdas@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 19:23:32 by kagdas            #+#    #+#             */
/*   Updated: 2026/05/19 12:20:26 by kagdas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	int		slen;
	char	*ptr;
	int		i;

	slen = ft_strlen(s);
	ptr = (char *)malloc(slen + 1);
	if (!ptr)
		return (NULL);
	i = 0;
	while (i < slen)
	{
		ptr[i] = s[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}
