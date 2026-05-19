/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kagdas <kagdas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 11:52:48 by kagdas            #+#    #+#             */
/*   Updated: 2026/05/19 11:52:49 by kagdas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int	is_sep(char c)
{
	return (c == ' ' || c == '\t' || c == '\r'
		|| c == '\n' || c == '\v' || c == '\f'
		|| c == '<' || c == '>' || c == '|');
}

void	quote_check(char c, char *quote)
{
	if (*quote == 0 && (c == '\'' || c == '"'))
		*quote = c;
	else if (*quote == c)
		*quote = 0;
}

static int	is_space_char(char c)
{
	return (c == ' ' || c == '\t' || c == '\r'
		|| c == '\n' || c == '\v' || c == '\f');
}

void	skip_spaces(char *input, int *i)
{
	while (input[*i] && is_space_char(input[*i]))
		(*i)++;
}

int	skip_escaped_char(char *s, int *i, char quote)
{
	if (s[*i] != '\\' || quote == '\'')
		return (0);
	if (quote == 0)
	{
		(*i)++;
		if (s[*i])
			(*i)++;
		return (1);
	}
	if (quote == '"' && (s[*i + 1] == '$' || s[*i + 1] == '"'
			|| s[*i + 1] == '\\' || s[*i + 1] == '`'))
	{
		(*i) += 2;
		return (1);
	}
	return (0);
}
