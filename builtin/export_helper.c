#include "builtin.h"

static void	free_str_arr(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

static void	print_env_format(t_envp *tmp)
{
	if (tmp->value == NULL)
		printf("declare -x %s\n", tmp->key);
	else if (tmp->value[0] == '\0')
		printf("declare -x %s=\"\"\n", tmp->key);
	else
		printf("declare -x %s=\"%s\"\n", tmp->key, tmp->value);
}

char	**find_env_arr(t_envp **env)
{
	int		len;
	int		i;
	t_envp	*tmp;
	char	**env_arr;

	len = 0;
	tmp = *env;
	while (tmp)
	{
		len++;
		tmp = tmp->next;
	}
	env_arr = malloc(sizeof(char *) * (len + 1));
	if (!env_arr)
		return (NULL);
	i = 0;
	tmp = *env;
	while (tmp)
	{
		env_arr[i++] = ft_strdup(tmp->key);
		tmp = tmp->next;
	}
	env_arr[i] = NULL;
	return (env_arr);
}

char	**sort_env_arr(t_envp **env)
{
	int		i;
	int		j;
	char	**env_arr;
	char	*env_tmp;

	env_arr = find_env_arr(env);
	if (!env_arr)
		return (NULL);
	i = 0;
	while (env_arr[i])
	{
		j = i + 1;
		while (env_arr[j])
		{
			if (ft_strcmp(env_arr[i], env_arr[j]) > 0)
			{
				env_tmp = env_arr[i];
				env_arr[i] = env_arr[j];
				env_arr[j] = env_tmp;
			}
			j++;
		}
		i++;
	}
	return (env_arr);
}

void	print_sorted_envs(t_envp **env)
{
	char	**env_arr;
	t_envp	*tmp;
	int		i;

	env_arr = sort_env_arr(env);
	if (!env_arr)
		return ;
	i = 0;
	while (env_arr[i])
	{
		tmp = *env;
		while (tmp)
		{
			if (ft_strcmp(tmp->key, env_arr[i]) == 0)
			{
				print_env_format(tmp);
				break ;
			}
			tmp = tmp->next;
		}
		i++;
	}
	free_str_arr(env_arr);
}
