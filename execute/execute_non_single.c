#include "execute.h"

static void	update_parent_fds(t_cmds *cmd, int *prev_fd, int fd[2])
{
	if (*prev_fd != STDIN_FILENO)
		close(*prev_fd);
	if (!cmd->next)
		return ;
	close(fd[1]);
	*prev_fd = fd[0];
}

static void	update_status_from_wait(pid_t pid, pid_t last_pid,
	int status, int *last_status)
{
	if (pid != last_pid)
		return ;
	if (WIFEXITED(status))
		*last_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		*last_status = 128 + WTERMSIG(status);
}

static int	wait_all_children(pid_t last_pid)
{
	pid_t	pid;
	int		status;
	int		last_status;

	last_status = 1;
	pid = wait(&status);
	while (pid > 0)
	{
		update_status_from_wait(pid, last_pid, status, &last_status);
		pid = wait(&status);
	}
	return (last_status);
}

int	execute_non_single(t_cmds **cmd, t_envp **env)
{
	int		fd[2];
	int		prev_fd;
	pid_t	pid;
	pid_t	last_pid;
	t_cmds *tmp;

	tmp = *cmd;
	prev_fd = STDIN_FILENO;
	last_pid = -1;
	while (tmp)
	{
		if (tmp->next && pipe(fd) < 0)
		{
			perror("pipe");
			return (1);
		}
		//free_envp_list(env); /////////////////test
		pid = create_child(&tmp, env, prev_fd, fd);
		if (pid < 0)
			return (1);
		update_parent_fds(tmp, &prev_fd, fd);
		last_pid = pid;
		tmp = tmp->next;
	}
	//free_cmd_list(cmd);
	//free_envp_list(env); // bunu koyarsam env leri komple göremiyorum
	return (wait_all_children(last_pid));
}
