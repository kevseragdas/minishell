#include "builtin.h"

static int	is_var_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}

char	*find_env_value(t_envp *env, char *key)
{
	size_t	len;

	if (!key || !env)
		return (NULL);
	len = ft_strlen(key);
	while (env)
	{
		if (ft_strncmp(env->key, key, len) == 0 && env->key[len] == '\0')
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

static char	*append_char(char *str, char c)
{
	char	*new_str;
	size_t	len;

	if (!str)
	{
		new_str = malloc(2);
		if (!new_str)
			return (NULL);
		new_str[0] = c;
		new_str[1] = '\0';
		return (new_str);
	}
	len = ft_strlen(str);
	new_str = malloc(len + 2);
	if (!new_str)
	{
		free(str);
		return (NULL);
	}
	ft_memcpy(new_str, str, len);
	new_str[len] = c;
	new_str[len + 1] = '\0';
	free(str);
	return (new_str);
}

static char	*append_str(char *dst, const char *src)
{
	char	*new_str;
	size_t	len1;
	size_t	len2;

	if (!src)
		return (dst);
	if (!dst)
		return (ft_strdup(src));
	len1 = ft_strlen(dst);
	len2 = ft_strlen(src);
	new_str = malloc(len1 + len2 + 1);
	if (!new_str)
	{
		free(dst);
		return (NULL);
	}
	ft_memcpy(new_str, dst, len1);
	ft_memcpy(new_str + len1, src, len2);
	new_str[len1 + len2] = '\0';
	free(dst);
	return (new_str);
}

static char	*expand_var(char *str, int *i, t_envp *env, int last_status)
{
	char	*key;
	char	*value;
	char	*status_str;
	int		start;

	if (str[*i + 1] == '?')
	{
		(*i) += 2;
		status_str = ft_itoa(last_status);
		return (status_str);
	}
	if (!str[*i + 1] || (!is_var_char(str[*i + 1]) && str[*i + 1] != '?'))
	{
		(*i)++;
		return (ft_strdup("$"));
	}
	start = *i + 1;
	while (str[start] && is_var_char(str[start]))
		start++;
	key = ft_substr(str, *i + 1, start - (*i + 1));
	if (!key)
		return (NULL);
	value = find_env_value(env, key);
	free(key);
	*i = start;
	if (!value)
		return (ft_strdup(""));
	return (ft_strdup(value));
}

static char	*process_word(char *str, t_envp *env, int last_status)
{
	char	*result;
	char	*tmp;
	int		i;
	char	quote;

	result = ft_strdup("");
	if (!result)
		return (NULL);
	i = 0;
	quote = 0;
	while (str[i])
	{
		if (str[i] == '\'' && quote == 0)
		{
			quote = '\'';
			i++;
		}
		else if (str[i] == '\'' && quote == '\'')
		{
			quote = 0;
			i++;
		}
		else if (str[i] == '"' && quote == 0)
		{
			quote = '"';
			i++;
		}
		else if (str[i] == '"' && quote == '"')
		{
			quote = 0;
			i++;
		}
		else if (str[i] == '$' && quote != '\'')
		{
			tmp = expand_var(str, &i, env, last_status);
			if (!tmp)
				return (free(result), NULL);
			result = append_str(result, tmp);
			free(tmp);
			if (!result)
				return (NULL);
		}
		else
		{
			result = append_char(result, str[i]);
			if (!result)
				return (NULL);
			i++;
		}
	}
	return (result);
}

void	expand_tokens(t_tokens *tokens, t_envp *env, int last_status)
{
	char	*new_value;

	while (tokens)
	{
		if (tokens->type == WORD
			&& !(tokens->prev && tokens->prev->type == HEREDOC))
		{
			new_value = process_word(tokens->value, env, last_status);
			if (new_value)
			{
				free(tokens->value);
				tokens->value = new_value;
			}
		}
		else if (tokens->type == WORD
			&& tokens->prev && tokens->prev->type == HEREDOC)
		{
			new_value = process_word(tokens->value, NULL, last_status);
			if (new_value)
			{
				free(tokens->value);
				tokens->value = new_value;
			}
		}
		tokens = tokens->next;
	}
}