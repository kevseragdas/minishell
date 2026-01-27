/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kagdas <kagdas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 20:29:31 by kagdas            #+#    #+#             */
/*   Updated: 2025/06/30 13:47:50 by kagdas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_cnt(int n)
{
	int	count;

	count = 0;
	if (n < 0)
	{
		n = -n;
		count++;
	}
	while (n != 0)
	{
		n = n / 10;
		count++;
	}
	return (count);
}

static char	*ft_cpy(int n, int count)
{
	char	*ptr;
	char	sign;

	sign = 0;
	if (n < 0)
	{
		n = -n;
		sign = 1;
	}
	ptr = malloc(count + 1);
	if (!ptr)
		return (NULL);
	if (sign == 1)
		ptr[0] = '-';
	ptr[count] = '\0';
	while (n != 0)
	{
		ptr[count - 1] = (n % 10) + 48;
		n = n / 10;
		count--;
	}
	return (ptr);
}

char	*ft_itoa(int n)
{
	int		count;
	char	*ptr;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n == 0)
	{
		ptr = malloc(2);
		if (!ptr)
			return (NULL);
		ptr[0] = '0';
		ptr[1] = '\0';
		return (ptr);
	}
	count = ft_cnt(n);
	ptr = ft_cpy(n, count);
	return (ptr);
}
