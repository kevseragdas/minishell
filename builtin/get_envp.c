#include "builtin.h"

static int	find_equal_sign(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	return (i);
}

void	find_key_value(char *env_string, char **key, char **value)
{
	int	i;

	i = find_equal_sign(env_string);
	if (env_string[i] == '\0')
	{
		*key = ft_strdup(env_string);
		*value = NULL;
	}
	else if (env_string[i] == '=' && env_string[i + 1] == '\0')
	{
		*key = ft_substr(env_string, 0, i);
		*value = ft_strdup("");
	}
	else
	{
		*key = ft_substr(env_string, 0, i);
		*value = ft_strdup(env_string + i + 1);
	}
}

static t_envp	*get_envp_helper(char *env_string)
{
	t_envp	*res;
	char	*key;
	char	*value;

	if (!env_string)
		return (NULL);
	key = NULL;
	value = NULL;
	res = malloc(sizeof(t_envp));
	if (!res)
		return (NULL);
	find_key_value(env_string, &key, &value);
	res->key = key;
	res->value = value;
	res->next = NULL;
	return (res);
}

void	get_envp(t_envp **env_head, char **envp)
{
	t_envp	*tail;
	t_envp	*new;
	t_envp	*head;
	int		i;

	i = 0;
	head = NULL;
	while (envp[i])
	{
		new = get_envp_helper(envp[i++]);
		if (!new)
		{
			free_envp_list(&head);
			return ;
		}
		if (!head)
			head = new;
		else
			tail->next = new;
		tail = new;
	}
	*env_head = head;
}

void	free_envp_list(t_envp **envp_list)
{
	t_envp	*tmp;

	tmp = *envp_list;
	while (tmp)
	{
		free(tmp->key);
		free(tmp->value);
		*envp_list = tmp->next;
		free(tmp);
		tmp = *envp_list;
	}
}
