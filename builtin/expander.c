#include "builtin.h"

static int	handle_quotes(char c, char *quote, int *i)
{
	if ((c == '\'' || c == '"') && *quote == 0)
		*quote = c;
	else if (*quote && c == *quote)
		*quote = 0;
	else
		return (0);
	(*i)++;
	return (1);
}

static char	*process_word(char *str, t_envp *env, int stat)
{
	char	*res;
	char	*tmp;
	int		i;
	char	q;

	res = ft_strdup("");
	i = 0;
	q = 0;
	while (str && str[i] && res)
	{
		if (handle_quotes(str[i], &q, &i))
			continue ;
		if (str[i] == '$' && q != '\'')
		{
			tmp = expand_var(str, &i, env, stat);
			res = append_str(res, tmp);
			free(tmp);
		}
		else
			res = append_char(res, str[i++]);
	}
	return (res);
}

void	expand_tokens(t_tokens *tokens, t_envp *env, int last_status)
{
	char	*new_value;
	t_envp	*curr_env;

	while (tokens)
	{
		if (tokens->type == WORD)
		{
			curr_env = env;
			if (tokens->prev && tokens->prev->type == HEREDOC)
				curr_env = NULL;
			new_value = process_word(tokens->value, curr_env, last_status);
			if (new_value)
			{
				free(tokens->value);
				tokens->value = new_value;
			}
		}
		tokens = tokens->next;
	}
}
