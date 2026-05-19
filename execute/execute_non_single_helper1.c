/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_non_single_helper1.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kagdas <kagdas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 11:50:58 by kagdas            #+#    #+#             */
/*   Updated: 2026/05/19 11:50:59 by kagdas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static int	is_env_modifying_builtin(char *name)
{
	if (!name)
		return (0);
	if (!ft_strcmp(name, "export") || !ft_strcmp(name, "unset"))
		return (1);
	if (!ft_strcmp(name, "cd") || !ft_strcmp(name, "exit"))
		return (1);
	return (0);
}

void	run_builtin_in_child(t_cmds **cmd, t_envp **env)
{
	int		status;

	if (!is_env_modifying_builtin((*cmd)->argv[0]))
	{
		status = exec_builtin(cmd, env, 0);
		free_envp_list(env);
		free_cmd_list(cmd);
		exit(status);
	}
	status = exec_builtin(cmd, env, 0);
	free_cmd_list(cmd);
	free_envp_list(env);
	exit(status);
}

void	setup_pipe_input(int prev_fd)
{
	if (prev_fd == STDIN_FILENO)
		return ;
	if (dup2(prev_fd, STDIN_FILENO) < 0)
	{
		perror("dup2");
		exit(1);
	}
	close(prev_fd);
}

void	setup_pipe_output(t_cmds *cmd, int fd[2])
{
	if (!cmd->next)
		return ;
	if (dup2(fd[1], STDOUT_FILENO) < 0)
	{
		perror("dup2");
		exit(1);
	}
	close(fd[0]);
	close(fd[1]);
}
