/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kagdas <kagdas@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 11:50:42 by kagdas            #+#    #+#             */
/*   Updated: 2026/05/19 12:17:33 by kagdas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	pwd_builtin(void)
{
	char	buff[4096];

	if (getcwd(buff, sizeof(buff)) == NULL)
	{
		print_error("getcwd() error!\n");
		return (1);
	}
	printf("%s\n", buff);
	return (0);
}
