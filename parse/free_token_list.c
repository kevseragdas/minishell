/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_token_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kagdas <kagdas@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 11:52:46 by kagdas            #+#    #+#             */
/*   Updated: 2026/05/19 12:21:59 by kagdas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void	free_token_list(t_tokens **tokens)
{
	t_tokens	*tmp;

	while (*tokens)
	{
		tmp = (*tokens)->next;
		free((*tokens)->value);
		free(*tokens);
		*tokens = tmp;
	}
}
