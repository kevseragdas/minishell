#include "execute.h"

int	is_directory(char *path)
{
	struct stat	st;

	if (stat(path, &st) == -1)
		return (0);
	return (S_ISDIR(st.st_mode));
}

void	errno_handler(void)
{
	if (errno == EACCES)
	{
		perror("minishell");
		exit(126);
	}
	else if (errno == ENOENT)
	{
		perror("minishell");
		exit(127);
	}
	else if (errno == EISDIR)
	{
		perror("minishell");
		exit(126);
	}
	perror("minishell");
	exit(1);
}

int	exec_external(t_cmds *cmd, t_envp *env)
{
	char	*path;
	int		status;
	char	**arr_env;

	path = NULL;
	status = find_path(cmd->argv[0], &path, env);
	if (status)
	{
		print_command_error(cmd->argv[0], status);
		exit(status);
	}
	if (is_directory(path))
	{
		write(2, "minishell: ", 11);
		write(2, path, ft_strlen(path));
		write(2, ": Is a directory\n", 17);
		free(path);
		exit(126);
	}
	arr_env = get_arr_env(env);
	execve(path, cmd->argv, arr_env);
	free(path);
	free_2d_arr(arr_env);
	errno_handler();
	return (1);
}
