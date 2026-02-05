#ifndef PARSE_H
#define PARSE_H

# include "../libft/libft.h" 
# include <readline/readline.h>
# include <readline/history.h>





/////////////////////////////
// token list structure and functions:

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

void    free_token_list(t_tokens **tokens);
int check_token_syntax(t_tokens **token);

t_tokens	*lexer(char *input);

////////////////////////////////
// for cmds until pipe and functions:

typedef struct s_redirs{
    t_token_type type;
    char *target;
    int fd;
    struct s_redirs *next;
} t_redirs ;

typedef struct s_cmds {
    char **argv;
    t_redirs *redirs;
    int in_fd;
    int out_fd;
    struct s_cmds *next;
} t_cmds ;

void    find_redirs(t_cmds **cmd, t_tokens *tmp);
void    free_redirs(t_redirs **redir);
void    free_cmd_list(t_cmds **cmd_list);
t_cmds    *create_cmd_list(t_tokens *tmp);


/////////////////////////////////////////////


#endif