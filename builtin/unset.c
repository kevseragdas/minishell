#include "builtin.h"

int	is_valid_identifier(char *arg)
{
	int	j;

	if (!arg || !arg[0])
		return (0);
	if (!(ft_isalpha(arg[0]) || arg[0] == '_'))
		return (0);
	j = 1;
	while (arg[j] && arg[j] != '=')
	{
		if (!(ft_isalnum(arg[j]) || arg[j] == '_'))
			return (0);
		j++;
	}
	return (1);
}

static int	unset_free(t_envp *tmp)
{
	free(tmp->key);
	free(tmp->value);
	free(tmp);
	return (0);
}

static int	unset_helper(char *argv, t_envp **env)
{
	t_envp	*tmp;
	t_envp	*pre;

	pre = *env;
	if (!pre)
		return (0);
	if (ft_strcmp(argv, pre->key) == 0)
	{
		*env = pre->next;
		return (unset_free(pre));
	}
	while (pre->next)
	{
		if (ft_strcmp(argv, pre->next->key) == 0)
		{
			tmp = pre->next;
			pre->next = tmp->next;
			return (unset_free(tmp));
		}
		pre = pre->next;
	}
	return (0);
}

static void	print_unset_error(char *arg)
{
	write(2, "unset: `", 8);
	write(2, arg, ft_strlen(arg));
	write(2, "`: not a valid identifier\n", 26);
}

int	unset_builtin(t_cmds *cmd, t_envp **env)
{
	int	i;
	int	status;

	i = 1;
	status = 0;
	while (cmd->argv[i])
	{
		if (!is_valid_identifier(cmd->argv[i]))
		{
			print_unset_error(cmd->argv[i]);
			status = 1;
		}
		else
			unset_helper(cmd->argv[i], env);
		i++;
	}
	return (status);
}
