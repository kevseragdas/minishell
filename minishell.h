#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"  

void    free_token_list(t_tokens **tokens);

int		is_empty(char *input);
char 	*del_quotes(char *input);
int 	is_one_quote(char *input, char c);
char 	**word_count(char *input);
int		num_of_word(char *input);
int 	get_word_len(char *input, int index);
int 	is_quote(char c);


typedef enum s_token_type {
    WORD,
    PIPE,
    REDIR_IN,
    REDIR_OUT,
    REDIR_APPEND,
    HEREDOC
} t_token_type ;

typedef struct s_tokens {
    t_token_type type;
    char    *value;
    struct s_tokens *prev;
    struct s_tokens *next;
    
} t_tokens ;



#endif