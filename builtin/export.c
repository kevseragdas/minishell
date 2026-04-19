#include "builtin.h"

static void	new_key_value(t_envp **env, char **key, char **value)
{
	t_envp	*new_env;
	t_envp	*tmp;

	new_env = malloc(sizeof(t_envp));
	if (!new_env)
		return ;
	new_env->key = ft_strdup(*key);
	if (*value)
		new_env->value = ft_strdup(*value);
	else
		new_env->value = NULL;
	new_env->next = NULL;
	if (!*env)
	{
		*env = new_env;
		free(*key);
		free(*value);
		return ;
	}
	tmp = *env;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_env;
	free(*key);
	free(*value);
}

static void	is_there_key(char *argv, t_envp **env)
{
	char	*key;
	char	*value;
	t_envp	*tmp;

	key = NULL;
	value = NULL;
	tmp = *env;
	find_key_value(argv, &key, &value);
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
		{
			if (ft_strchr(argv, '='))
			{
				free(tmp->value);
				if (value)
					tmp->value = ft_strdup(value);
				else
					tmp->value = NULL;
			}
			free(key);
			free(value);
			return ;
		}
		tmp = tmp->next;
	}
	new_key_value(env, &key, &value);
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
			write(2, "export: `", 9);
			write(2, cmd->argv[i], ft_strlen(cmd->argv[i]));
			write(2, "`: not a valid identifier\n", 26);
			status = 1;
		}
		else
			is_there_key(cmd->argv[i], env);
		i++;
	}
	return (status);
}