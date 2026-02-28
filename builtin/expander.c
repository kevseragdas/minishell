#include "builtin.h"

int	is_var_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}

/* Listeden key'e karşılık gelen value'yu bulur */
char	*find_env_value(t_envp *env, char *key)
{
	size_t	len;

	if (!key || !env)
		return (NULL);
	len = ft_strlen(key);
	while (env)
	{
		if (ft_strncmp(env->key, key, len) == 0 
			&& env->key[len] == '\0')
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

/* $ işaretinden sonraki değişken adının uzunluğunu bulur */
int	get_var_len(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '?') // $? durumu için (exit status)
		return (1);
	if (ft_isdigit(str[i])) // $1 gibi sayılar için
		return (1);
	while (str[i] && is_var_char(str[i]))
		i++;
	return (i);
}
int	update_quote(int quote, char c)
{
	if (c == '\'' && quote != 2)
		return (quote == 0);
	if (c == '\"' && quote != 1)
		return ((quote == 0) * 2);
	return (quote);
}
int	calc_len(char *str, t_envp *env)
{
	int		i;
	int		len;
	int		quote;
	char	*tmp;
	
	i = -1;
	len = 0;
	quote = 0;
	while (str[++i])
	{
		if ((str[i] == '\'' && quote != 2) || (str[i] == '\"' && quote != 1))
			quote = update_quote(quote, str[i]);
		else if (str[i] == '$' && quote != 1 && (is_var_char(str[i + 1]) || str[i + 1] == '?'))
		{
			tmp = ft_substr(str, i + 1, get_var_len(&str[i + 1]));
			if (find_env_value(env, tmp))
				len += ft_strlen(find_env_value(env, tmp));
			free(tmp);
			i += get_var_len(&str[i + 1]);
		}
		else
			len++;
	}
	return (len);
}
