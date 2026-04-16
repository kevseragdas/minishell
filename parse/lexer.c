#include "parse.h"

static int	is_sep(char c)
{
	return (c == ' ' || c == '\t' || c == '<' || c == '>' || c == '|');
}

static void	quote_check(char c, char *quote)
{
	if (*quote == 0 && (c == '\'' || c == '"'))
		*quote = c;
	else if (*quote == c)
		*quote = 0;
}

static int	add_token(t_tokens **head, char *value, t_token_type type)
{
	t_tokens	*new_node;
	t_tokens	*temp;

	new_node = malloc(sizeof(t_tokens));
	if (!new_node)
	{
		free(value);
		return (1);
	}
	new_node->value = value;
	new_node->type = type;
	new_node->next = NULL;
	new_node->prev = NULL;
	if (*head == NULL)
		*head = new_node;
	else
	{
		temp = *head;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new_node;
		new_node->prev = temp;
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
	if (!word)
		return (0);
	if (add_token(head, word, WORD))
		return (0);
	return (1);
}

static int	handle_operator(char *s, int *i, t_tokens **head)
{
	if (s[*i] == '<' && s[*i + 1] == '<')
	{
		if (add_token(head, ft_strdup("<<"), HEREDOC))
			return (1);
		(*i) += 2;
	}
	else if (s[*i] == '>' && s[*i + 1] == '>')
	{
		if (add_token(head, ft_strdup(">>"), REDIR_APPEND))
			return (1);
		(*i) += 2;
	}
	else if (s[*i] == '|')
	{
		if (add_token(head, ft_strdup("|"), PIPE))
			return (1);
		(*i)++;
	}
	else if (s[*i] == '<')
	{
		if (add_token(head, ft_strdup("<"), REDIR_IN))
			return (1);
		(*i)++;
	}
	else if (s[*i] == '>')
	{
		if (add_token(head, ft_strdup(">"), REDIR_OUT))
			return (1);
		(*i)++;
	}
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
			{
				free_token_list(&head);
				return (NULL);
			}
		}
		else
		{
			if (!handle_word(input, &i, &head))
			{
				write(2, "minishell: unclosed quotes\n", 27);
				free_token_list(&head);
				return (NULL);
			}
		}
	}
	return (head);
}