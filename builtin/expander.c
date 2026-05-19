/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kagdas <kagdas@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 11:50:22 by kagdas            #+#    #+#             */
/*   Updated: 2026/05/19 12:17:07 by kagdas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static int	is_special_quote_char(char c)
{
	return (c == '$' || c == '"' || c == '\\' || c == '`');
}

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

static char	*handle_backslash(char *str, int *i, char q, char *res)
{
	if (q == 0)
	{
		(*i)++;
		if (str[*i])
		{
			res = append_char(res, str[*i]);
			(*i)++;
		}
	}
	else if (q == '"')
	{
		if (is_special_quote_char(str[*i + 1]))
			(*i)++;
		res = append_char(res, str[*i]);
		(*i)++;
	}
	return (res);
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
		if (str[i] == '\\' && q != '\'')
			res = handle_backslash(str, &i, q, res);
		else if (str[i] == '$' && q != '\'')
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
