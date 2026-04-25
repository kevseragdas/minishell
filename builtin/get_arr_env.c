#include "builtin.h"

static int	env_count(t_envp *env)
{
	int	count;

	count = 0;
	while (env)
	{
		count++;
		env = env->next;
	}
	return (count);
}

char	**get_arr_env(t_envp *env)
{
	char	**arr;
	char	*tmp_str;
	int		i;

	arr = malloc(sizeof(char *) * (env_count(env) + 1));
	if (!arr)
		return (NULL);
	i = 0;
	while (env)
	{
		if (env->value != NULL)
		{
			tmp_str = ft_strjoin(env->key, "=");
			arr[i] = ft_strjoin(tmp_str, env->value);
			free(tmp_str);
			i++;
		}
		env = env->next;
	}
	arr[i] = NULL;
	return (arr);
}
