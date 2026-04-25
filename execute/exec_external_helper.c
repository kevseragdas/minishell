#include "execute.h"

void	free_2d_arr(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	print_command_error(const char *cmd, int error_type)
{
	write(2, "minishell: ", 11);
	write(2, cmd, ft_strlen(cmd));
	if (error_type == 127)
	{
		if (ft_strchr(cmd, '/'))
			write(2, ": No such file or directory\n", 28);
		else
			write(2, ": command not found\n", 20);
	}
	else if (error_type == 126)
		write(2, ": Permission denied\n", 20);
}

static int	check_absolute_path(char *cmd, char **path)
{
	if (access(cmd, F_OK) != 0)
		return (127);
	if (access(cmd, X_OK) != 0)
		return (126);
	*path = ft_strdup(cmd);
	if (!*path)
		return (127);
	return (0);
}

static int	check_access(char **paths, char **path, char *cmd)
{
	int		i;
	int		f;
	char	*tmp;

	i = -1;
	f = 0;
	while (paths && paths[++i])
	{
		tmp = ft_strjoin(paths[i], "/");
		if (tmp)
		{
			*path = ft_strjoin(tmp, cmd);
			free(tmp);
		}
		if (*path && access(*path, X_OK) == 0)
			return (0);
		if (*path && access(*path, F_OK) == 0)
			f = 1;
		free(*path);
		*path = NULL;
	}
	return (127 - f);
}

int	find_path(char *cmd, char **path, t_envp *env)
{
	char	**paths;
	int		status;

	if (!cmd)
		return (127);
	if (ft_strchr(cmd, '/'))
		return (check_absolute_path(cmd, path));
	while (env && ft_strcmp(env->key, "PATH") != 0)
		env = env->next;
	if (!env || !env->value || !env->value[0])
		return (127);
	paths = ft_split(env->value, ':');
	status = check_access(paths, path, cmd);
	free_2d_arr(paths);
	return (status);
}
