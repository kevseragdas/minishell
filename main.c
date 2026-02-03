#include "minishell.h"

int main(int ac, char **av, char **envp)
{
    char        *input;
    t_tokens    *tokens;

    (void)ac; (void)av; (void)envp;
    while (1)
    {
        input = readline("minishell$ ");
        if (!input) 
            break;
        if (input[0] != '\0')
        {
            add_history(input);
            tokens = lexer(input);
            if (tokens)
            {
                print_tokens(tokens);
                free_token_list(&tokens);
            }
        }
        free(input);
    }
    return (0);
}