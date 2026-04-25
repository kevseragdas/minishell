#include "parse.h"

static int	add_token(t_tokens **head, char *value, t_token_type type)
{
	t_tokens	*new;
	t_tokens	*tmp;

	new = malloc(sizeof(t_tokens));
	if (!new)
		return (free(value), 1);
	new->value = value;
	new->type = type;
	new->next = NULL;
	new->prev = NULL;
	if (!*head)
		*head = new;
	else
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
		new->prev = tmp;
	}
	return (0);
}

static int	handle_word(char *s, int *i, t_tokens **head)
{
	int		start;
	char	quote;
	char	*word;

	start = *i;
	quote = 0;
	while (s[*i])
	{
		quote_check(s[*i], &quote);
		if (quote == 0 && is_sep(s[*i]))
			break ;
		(*i)++;
	}
	if (quote != 0)
		return (0);
	word = ft_substr(s, start, *i - start);
	if (!word || add_token(head, word, WORD))
		return (0);
	return (1);
}

static int	handle_double_op(char *s, int *i, t_tokens **head)
{
	if (s[*i] == '<' && s[*i + 1] == '<')
	{
		if (add_token(head, ft_strdup("<<"), HEREDOC))
			return (1);
		(*i) += 2;
		return (1);
	}
	if (s[*i] == '>' && s[*i + 1] == '>')
	{
		if (add_token(head, ft_strdup(">>"), REDIR_APPEND))
			return (1);
		(*i) += 2;
		return (1);
	}
	return (0);
}

static int	handle_operator(char *s, int *i, t_tokens **head)
{
	int	is_double;

	is_double = handle_double_op(s, i, head);
	if (is_double)
		return (0);
	if (s[*i] == '|')
		is_double = add_token(head, ft_strdup("|"), PIPE);
	else if (s[*i] == '<')
		is_double = add_token(head, ft_strdup("<"), REDIR_IN);
	else if (s[*i] == '>')
		is_double = add_token(head, ft_strdup(">"), REDIR_OUT);
	if (is_double)
		return (1);
	(*i)++;
	return (0);
}

t_tokens	*lexer(char *input)
{
	t_tokens	*head;
	int			i;

	head = NULL;
	i = 0;
	while (input[i])
	{
		while (input[i] && (input[i] == ' ' || input[i] == '\t'))
			i++;
		if (!input[i])
			break ;
		if (input[i] == '|' || input[i] == '<' || input[i] == '>')
		{
			if (handle_operator(input, &i, &head))
				return (free_token_list(&head), NULL);
		}
		else if (!handle_word(input, &i, &head))
		{
			write(2, "minishell: unclosed quotes\n", 27);
			return (free_token_list(&head), NULL);
		}
	}
	return (head);
}
