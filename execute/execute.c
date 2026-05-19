/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kagdas <kagdas@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 11:51:09 by kagdas            #+#    #+#             */
/*   Updated: 2026/05/19 12:18:13 by kagdas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

int	execute(t_cmds **cmd, t_envp **env)
{
	if (!cmd || !*cmd)
		return (0);
	if (prepare_heredocs(cmd, env) < 0)
		return (130);
	if ((*cmd)->next)
		return (execute_non_single(cmd, env));
	return (execute_single(cmd, env));
}
