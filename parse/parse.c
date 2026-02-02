#include "parse.h"

int is_space(char c)
{
    return (c == ' ' || c == '\t');
}

int is_quote(char c)
{
	return (c == '"' || c == '\'');
}
int	is_empty(char *input)
{
	int i;

	if (!input)
		return (0);
	i = 0;
	while (input[i])
	{
		if (input[i] == ' ' || input[i] == '\t')
			i++;
		else
			return (0);
	}
	return (1);
}

int is_one_quote(char *input, char c)
{
	int count;
	int	i;

	i = 0;
	count = 0;
	while (input[i])
	{
		if (input[i] == c)
			count++;
		i++;
	}
	if (count % 2 == 0)
		return (1);
	return (0);
}

char *del_quotes(char *input)
{
	int i = 0;
    int j = 0;
    char quote = 0;
    char *cleaned;

    cleaned = malloc(ft_strlen(input) + 1);
    if (!cleaned)
        return (NULL);

    while (input[i])
    {
        if (is_quote(input[i]))
        {
            if (quote == 0)
                quote = input[i];
            else if (quote == input[i])
                quote = 0;
            else
                cleaned[j++] = input[i];
        }
        else
            cleaned[j++] = input[i];
        i++;
    }
    cleaned[j] = '\0';
    return (cleaned);
	
}

int num_of_word(char *input)
{
    int i = 0;
    int count = 0;
    char quote_char;

    while (input[i])
    {
        while (input[i] && is_space(input[i]))
            i++;
        if (input[i])
            count++;
        while (input[i] && !is_space(input[i]))
        {
            if (is_quote(input[i]))
            {
                quote_char = input[i];
                i++;
                while (input[i] && input[i] != quote_char)
                    i++;
            }
            if (input[i])
                i++;
        }
    }
    return (count);
}

int get_word_len(char *input, int index)
{
    int i = 0;
    char quote = 0;
    while (input[index + i] && (!is_space(input[index + i]) || quote != 0))
    {
        if (is_quote(input[index + i]))
        {
            if (quote == 0)
                quote = input[index + i];
            else if (quote == input[index + i])
                quote = 0;
        }
        i++;
    }
    return (i);
}

char **word_count(char *input)
{
    int i = 0;
    int k = 0;
    int index = 0;
    int len = 0;
    int num;
    char **new;

    num = num_of_word(input);
    new = malloc(sizeof(char *) * (num + 1));
    if (!new)
        return (NULL);

    while (input[i] && index < num) 
    {
        while (is_space(input[i]))
            i++;
        if (input[i]) 
        {
            len = get_word_len(input, i);
            new[index] = malloc(len + 1);
            if (!new[index])
                 return (NULL);
            k = 0; 
            while (len > 0 && input[i])
            {
                new[index][k] = input[i];
                i++;
                k++;
                len--;
            }
            new[index][k] = '\0';
            index++;
        }
    }
    new[index] = NULL;
    return (new);
}

