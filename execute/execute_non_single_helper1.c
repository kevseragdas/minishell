#include "execute.h"

static t_envp	*clone_env_list(t_envp *env)
{
	t_envp	*head;
	t_envp	*tail;
	t_envp	*new;

	head = NULL;
	while (env)
	{
		new = malloc(sizeof(t_envp));
		if (!new)
			return (free_envp_list(&head), NULL);
		new->key = ft_strdup(env->key);
		new->value = NULL;
		if (env->value)
			new->value = ft_strdup(env->value);
		new->next = NULL;
		if (!head)
			head = new;
		else
			tail->next = new;
		tail = new;
		env = env->next;
	}
	return (head);
}

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

void	run_builtin_in_child(t_cmds *cmd, t_envp **env)
{
	t_envp	*tmp_env;
	int		status;

	if (!is_env_modifying_builtin(cmd->argv[0]))
		exit(exec_builtin(&cmd, env, 0));
	tmp_env = clone_env_list(*env);
	if (!tmp_env)
		exit(1);
	status = exec_builtin(&cmd, &tmp_env, 0);
	free_envp_list(&tmp_env);
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
