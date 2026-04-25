#include "execute.h"

static void	handle_enoexec(char *path, char **argv, char **arr_env)
{
	int		i;
	char	**new_argv;

	i = 0;
	while (argv[i])
		i++;
	new_argv = malloc(sizeof(char *) * (i + 2));
	if (!new_argv)
	{
		free(path);
		free_2d_arr(arr_env);
		exit(1);
	}
	new_argv[0] = "/bin/sh";
	new_argv[1] = path;
	i = 1;
	while (argv[i])
	{
		new_argv[i + 1] = argv[i];
		i++;
	}
	new_argv[i + 1] = NULL;
	execve("/bin/sh", new_argv, arr_env);
	free(new_argv);
}

static void	check_dir_and_exit(char *path)
{
	struct stat	st;

	if (stat(path, &st) != -1 && S_ISDIR(st.st_mode))
	{
		write(2, "minishell: ", 11);
		write(2, path, ft_strlen(path));
		write(2, ": Is a directory\n", 17);
		free(path);
		exit(126);
	}
}

static void	errno_handler(void)
{
	perror("minishell");
	if (errno == EACCES || errno == EISDIR)
		exit(126);
	if (errno == ENOENT)
		exit(127);
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
	check_dir_and_exit(path);
	arr_env = get_arr_env(env);
	execve(path, cmd->argv, arr_env);
	if (errno == ENOEXEC)
		handle_enoexec(path, cmd->argv, arr_env);
	free(path);
	free_2d_arr(arr_env);
	errno_handler();
	return (1);
}
