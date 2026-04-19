#include "builtin.h"

static int	is_numeric_arg(char *str)
{
	int	i;

	if (!str || !str[0])
		return (0);
	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static void	print_exit_numeric_error(char *arg)
{
	write(2, "minishell: exit: ", 17);
	write(2, arg, ft_strlen(arg));
	write(2, ": numeric argument required\n", 28);
}

int	exit_builtin(t_cmds **cmd, t_envp **env, int is_parent)
{
	long	status;

	if (!(*cmd)->argv[1])
	{
		if (is_parent)
		{
			free_cmd_list(cmd);
			free_envp_list(env);
			exit(0);
		}
		return (0);
	}
	if (!is_numeric_arg((*cmd)->argv[1]))
	{
		print_exit_numeric_error((*cmd)->argv[1]);
		if (is_parent)
		{
			free_cmd_list(cmd);
			free_envp_list(env);
			exit(2);
		}
		return (2);
	}
	if ((*cmd)->argv[2])
	{
		write(2, "minishell: exit: too many arguments\n", 36);
		return (1);
	}
	status = ft_atol((*cmd)->argv[1]);
	status = (unsigned char)status;
	if (is_parent)
	{
		free_cmd_list(cmd);
		free_envp_list(env);
		exit((int)status);
	}
	return ((int)status);
}
