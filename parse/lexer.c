
#include "parse.h"

int	is_sep(char c)
{
	return (c == ' ' || c == '\t' || c == '<' || c == '>' || c == '|');
}

void	quote_check(char c, char *quote)
{
	if (*quote == 0 && (c == '\'' || c == '"'))
		*quote = c;
	else if (*quote == c)
		*quote = 0;
}

int add_token(t_tokens **head, char *value, t_token_type type)
{
    t_tokens *new_node;
    t_tokens *temp;

    new_node = malloc(sizeof(t_tokens));
    if (!new_node)
        return (1);
    
    new_node->value = value;
    new_node->type = type;
    new_node->next = NULL;
    new_node->prev = NULL;

    if (*head == NULL) // Liste boşsa, bu ilk elemandır
        *head = new_node;
    else // Liste doluysa, sona kadar git ve ekle
    {
        temp = *head;
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = new_node;
        new_node->prev = temp;
    }
	return (0);
}

int	handle_word(char *s, int *i, t_tokens **head)
{
	int		start;
	char	quote;

	start = *i;
	quote = 0;
	while (s[*i])
	{
		quote_check(s[*i], &quote);
		// Eğer tırnak kapalıysa VE şu anki karakter ayırıcıysa
		if (quote == 0 && is_sep(s[*i]))
			break ;
		(*i)++;
	}
	if (quote != 0)
		return (0);
	// Kelimeyi kes ve listeye ekle
	add_token(head, ft_substr(s, start, *i - start), WORD);
	return (1);
}

void	handle_operator(char *s, int *i, t_tokens **head)
{
	if (s[*i] == '<' && s[*i + 1] == '<')
	{
		add_token(head, ft_strdup("<<"), HEREDOC);
		(*i) += 2;
	}
	else if (s[*i] == '>' && s[*i + 1] == '>')
	{
		add_token(head, ft_strdup(">>"), REDIR_APPEND);
		(*i) += 2;
	}
	else if (s[*i] == '|')
		add_token(head, ft_strdup("|"), PIPE), (*i)++;
	else if (s[*i] == '<')
		add_token(head, ft_strdup("<"), REDIR_IN), (*i)++;
	else if (s[*i] == '>')
		add_token(head, ft_strdup(">"), REDIR_OUT), (*i)++;
}

t_tokens	*lexer(char *input)
{
	t_tokens	*head;
	int			i;

	head = NULL;
	i = 0;
	while (input[i])
	{
		// Boşlukları atla
		while (input[i] && (input[i] == ' ' || input[i] == '\t'))
			i++;
		if (!input[i])
			break ;
		// Operatör mü Kelime mi?
		if (input[i] == '|' || input[i] == '<' || input[i] == '>')
			handle_operator(input, &i, &head);
		else
		{
			if (!handle_word(input, &i, &head))
			{
				write(2,"Error: Unclosed quotes\n", 24);
				free_token_list(&head);
				return (NULL);
			}
		}
	}
	return (head);
}