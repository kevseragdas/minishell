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
