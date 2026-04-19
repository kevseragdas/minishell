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

static int	check_access(char **paths, char **path, char *argv_0)
{
	int		i;
	int		found_file;
	char	*tmp_str;

	i = 0;
	found_file = 0;
	while (paths && paths[i])
	{
		tmp_str = ft_strjoin(paths[i], "/");
		if (!tmp_str)
			return (127);
		*path = ft_strjoin(tmp_str, argv_0);
		free(tmp_str);
		if (!*path)
			return (127);
		if (access(*path, F_OK) == 0)
			found_file = 1;
		if (access(*path, X_OK) == 0)
			return (0);
		free(*path);
		*path = NULL;
		i++;
	}
	if (found_file)
		return (126);
	return (127);
}

int	find_path(char *argv_0, char **path, t_envp *env)
{
	t_envp	*tmp;
	char	**paths;
	int		status;

	if (!argv_0)
		return (127);
	if (ft_strchr(argv_0, '/'))
	{
		if (access(argv_0, F_OK) != 0)
			return (127);
		if (access(argv_0, X_OK) != 0)
			return (126);
		*path = ft_strdup(argv_0);
		if (!*path)
			return (127);
		return (0);
	}
	tmp = env;
	while (tmp && ft_strcmp(tmp->key, "PATH"))
		tmp = tmp->next;
	if (!tmp || !tmp->value || tmp->value[0] == '\0')
		return (127);
	paths = ft_split(tmp->value, ':');
	if (!paths)
		return (127);
	status = check_access(paths, path, argv_0);
	free_2d_arr(paths);
	return (status);
}