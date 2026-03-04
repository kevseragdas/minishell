#include "builtin.h"

static int	env_count(t_envp *env)
{
	int		count;
	t_envp	*tmp;

	count = 0;
	tmp = env;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	return (count);
}

char **get_arr_env(t_envp *env)
{
    char	**arr;
	char	*tmp_str;
	int		i;
	int		count;

	count = env_count(env);
	arr = (char **)malloc(sizeof(char *) * (count + 1));
	if (!arr)
		return (NULL);
	i = 0;
	while (env)
	{
		tmp_str = ft_strjoin(env->key, "=");
		arr[i] = ft_strjoin(tmp_str, env->value);
		free(tmp_str);
		i++;
		env = env->next;
	}
	arr[i] = NULL;
	return (arr);
}