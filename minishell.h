#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"  

typedef struct s_cmd {
    char			**args;    // ["ls", "-l", NULL]
    int				fd_in;
    int				fd_out;
    struct s_cmd	*next;
} t_cmd;

typedef enum s_token_type {
    WORD,
    PIPE,
    REDIR_IN,
    REDIR_OUT,
    REDIR_APPEND,
    HEREDOC
} t_token_type ;

typedef struct s_tokens {
    t_token_type	type;
    char			*value;
    struct s_tokens	*prev;
    struct s_tokens	*next;
    
} t_tokens ;


void        free_token_list(t_tokens **tokens);
void        check_token_syntax(t_tokens **token);
int	        is_sep(char c);
void	    quote_check(char c, char *quote);
void        add_token(t_tokens **head, char *value, t_token_type type);
int	        handle_word(char *s, int *i, t_tokens **head);
void	    handle_operator(char *s, int *i, t_tokens **head);
t_tokens	*lexer(char *input);
int         get_env_len(char **envp);
char        **copy_env(char **envp);
char        *get_env_value(char *var_name, char **env);

#endif