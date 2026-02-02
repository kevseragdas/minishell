#include "parse.h"

void syntax_error(t_tokens **token)
{
    free_token_list(token);
    write(2, "minishell: syntax error!\n", 26);
}

void check_token_syntax(t_tokens **token)
{
    t_tokens    *tmp;

    tmp = *token;
    if(!tmp)
        return ;
    //first token shouldn't be PIPE
    if(tmp->type == 1)
        return (syntax_error(token));
    
    while(tmp && tmp->next)
    {
        while(tmp && tmp->type == 0)
            tmp = tmp->next;
        // after while i will have a token which is not WORD
        // the next token after this must be WORD, not PIPE REDIR etc.
        if(tmp && tmp->next && tmp->next->type != 0)
            return (syntax_error(token));
        if(tmp && tmp->next)
            tmp = tmp->next;
    }
    // last token should be WORD, not PIPE REDIR etc.
    if(tmp && tmp->type != 0)
        return (syntax_error(token));
}
