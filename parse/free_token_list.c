#include "parse.h"

void    free_token_list(t_tokens **tokens)
{
    t_tokens    *tmp;

    while(*tokens)
    {
        tmp = (*tokens)->next;
        free(*tokens);
        *tokens = tmp;
    }
}