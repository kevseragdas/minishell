#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"  

int	is_empty(char *input);
char *del_quotes(char *input, char c);
int is_one_quote(char *input, char c);
int num_of_word(char *input);
char **word_count(char *input);

#endif