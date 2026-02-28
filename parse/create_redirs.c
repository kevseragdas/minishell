#include "parse.h"

void    find_redirs(t_cmds **cmd, t_tokens *tmp)
{
    t_redirs *new_rdr;
    t_redirs *curr_rdr;
    t_redirs *head_rdr;

    head_rdr = NULL;
    curr_rdr = NULL;
    while(tmp && tmp->type != PIPE)
    {
        if(tmp->type != WORD && tmp->next)
        {
            new_rdr = malloc(sizeof(t_redirs));
            if(!new_rdr)
                return ;
            new_rdr->type = tmp->type;
            new_rdr->target = ft_strdup(tmp->next->value);
            new_rdr->fd = -1;
            new_rdr->next = NULL;
            if(!head_rdr)
                head_rdr = new_rdr;
            else
                curr_rdr->next = new_rdr;
            curr_rdr = new_rdr;
        }
        tmp = tmp->next;
    }
    (*cmd)->redirs = head_rdr;
}

void    free_redirs(t_redirs **redir)
{
    t_redirs    *tmp;
    
    while(*redir)
    {
        tmp = *redir;
        free(tmp->target);
        *redir = (*redir)->next;
        free(tmp);
    }
}