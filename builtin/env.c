/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kagdas <kagdas@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 11:50:07 by kagdas            #+#    #+#             */
/*   Updated: 2026/05/19 12:16:53 by kagdas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	env_builtin(t_cmds **cmd, t_envp **env_list)
{
	t_envp	*tmp;

	if ((*cmd)->argv[1])
	{
		write(2, "env: ", 5);
		write(2, (*cmd)->argv[1], ft_strlen((*cmd)->argv[1]));
		write(2, ": No such file or directory\n", 28);
		free_envp_list(env_list);
		free_cmd_list(cmd);
		return (127);
	}
	tmp = *env_list;
	while (tmp)
	{
		if (tmp->key && tmp->value)
			printf("%s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
	return (0);
}
