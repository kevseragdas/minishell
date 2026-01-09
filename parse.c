#include "minishell.h"

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
	while (input)
	{
		if (input[i] == c)
			count++;
		i++;
	}
	if (count % 2 == 0)
		return (1);
	return (0);
}

char *del_quotes(char *input, char c)
{
	int	i;
	int	j;
	char	*new;

	i = 0;
	j = 0;
	while (input[i])
	{
		if (input[i] == c)
			i++;
		new[j] = input[i];
		j++;
		i++;
	}
	return (new);
}

int *len_of_word(char *input)
{
	int i;
	int j;
	int *length;
	int len;
	int num;

	num = num_of_word(input);
	length = malloc(sizeof(int) * (num + 1));
	j = 0;
	len = 0;
	i = 0;
	while (input[i])
	{
		while(input[i] && input[i] == ' ')
			i++;
		len = i;
		printf("len: %d\n", len);
		if(input[i] && input[i] != '"')
		{
			while(input[i] && input[i] != ' ')
				i++;
			length[j] = i - len;
			j++;
		}
		else if (input[i] && input[i] == '"')
		{
			i++;
			while (input[i] && input[i] != '"')
				i++;
			i++;
			length[j] = i - len - 2;
			j++;
		}
	}
	printf("j: %d\n", j);
	length[j] = '\0';
	return (length);
}

int num_of_word(char *input)
{
	int i;
	int	count;

	count = 0;
	i = 0;
	while (input[i])
	{
		while (input[i] == ' ' || input[i] == '\t')
			i++;
		if (input[i])
			count++;
		while (input[i] && (input[i] != ' ' && input[i] != '\t'))
		{
			if (input[i] == '"' || input[i] == '\'')
			{
				count++;
				i++;
				while (input[i] != '"' && input[i] != '\'')
					i++;
				i++;
			}
			while (input[i] && (input[i] != ' ' && input[i] != '\t'))
				i++;
			i++;
		}
		i++;
	}
	return (count);
}
char **word_count(char *input)
{
	int	i;
	int j;
	int k;
	int num;
	char **new;

	num = num_of_word(input);
	new = malloc(num + 1);
	j = 0;
	while (input[i] && j < num)
	{
		while (input[i] == ' ' || input[i] == '\t')
			i++;
		while (input[i] && (input[i] != ' ' && input[i] != '\t'))
		{
			if (input[i] == '"' || input[i] == '\'')
			{
				i++;
				while (input[i] && (input[i] != '"' && input[i] != '\''))
				{
					new[j][k] = input[i];
					k++;
					i++;
				}
				i++;
				j++;
				k = 0;
			}
			else
			{
				while(input[i] && (input[i] != ' ' && input[i] != '\t'))
				{
					new[j][k] = input[i];
					k++;
					i++;
					if(input[i] == ' ' || input[i] == '\t')
						j++;
				}
				k = 0;
			}
		}
	}
	return (new);
}
