#include "builtin.h"

static void	update_env_value(t_envp *tmp, char *argv, char *value)
{
	if (ft_strchr(argv, '='))
	{
		free(tmp->value);
		if (value)
			tmp->value = ft_strdup(value);
		else
			tmp->value = NULL;
	}
}

static void	print_export_error(char *arg)
{
	write(2, "export: `", 9);
	write(2, arg, ft_strlen(arg));
	write(2, "`: not a valid identifier\n", 26);
}

static void	new_key_value(t_envp **env, char *key, char *value)
{
	t_envp	*new_env;
	t_envp	*tmp;

	new_env = malloc(sizeof(t_envp));
	if (!new_env)
		return ;
	new_env->key = ft_strdup(key);
	if (value)
		new_env->value = ft_strdup(value);
	else
		new_env->value = NULL;
	new_env->next = NULL;
	if (!*env)
	{
		*env = new_env;
		return ;
	}
	tmp = *env;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_env;
}

static void	is_there_key(char *argv, t_envp **env)
{
	char	*key;
	char	*value;
	t_envp	*tmp;

	key = NULL;
	value = NULL;
	find_key_value(argv, &key, &value);
	tmp = *env;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
		{
			update_env_value(tmp, argv, value);
			free(key);
			free(value);
			return ;
		}
		tmp = tmp->next;
	}
	new_key_value(env, key, value);
	free(key);
	free(value);
}

int	export_builtin(t_cmds *cmd, t_envp **env)
{
	int	i;
	int	status;

	i = 1;
	status = 0;
	if (!cmd->argv[1])
	{
		print_sorted_envs(env);
		return (0);
	}
	while (cmd->argv[i])
	{
		if (!is_valid_identifier(cmd->argv[i]))
		{
			print_export_error(cmd->argv[i]);
			status = 1;
		}
		else
			is_there_key(cmd->argv[i], env);
		i++;
	}
	return (status);
}
