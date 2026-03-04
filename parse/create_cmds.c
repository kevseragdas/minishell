#include "parse.h"

int find_argv_num(t_tokens *tmp)
{
    int argv_num;

    argv_num = 0;
    while(tmp && tmp->type != PIPE)
    {
        if(!tmp->prev || (tmp->prev && (tmp->prev->type == WORD || tmp->prev->type == PIPE)))
            argv_num++;
        tmp = tmp->next;
    }
    return (argv_num);
}

void    find_argv(t_cmds **cmd, t_tokens *tmp)
{
    int i;
    int argv_num;

    i = 0;
    argv_num = find_argv_num(tmp);
    (*cmd)->argv = malloc((argv_num + 1) * sizeof(char *));
    if(!((*cmd)->argv))
        return ;
    while(tmp && tmp->type != PIPE)
    {
        if(tmp->type == WORD && i < argv_num)
        {
            if(!tmp->prev || (tmp->prev && (tmp->prev->type == WORD || tmp->prev->type == PIPE)))
            {
                (*cmd)->argv[i] = ft_strdup(tmp->value);
                i++;
            }
        }
        tmp = tmp->next;
    }
    (*cmd)->argv[i] = NULL;
}


t_cmds    *create_cmd_list(t_tokens *tmp)
{
    t_cmds  *cmd;

    cmd = malloc(sizeof(t_cmds));
    if(!cmd)
        return (NULL);

    find_redirs(&cmd, tmp);
    find_argv(&cmd,  tmp);

    cmd->in_fd = STDIN_FILENO;
    cmd->out_fd =STDOUT_FILENO;

    while (tmp && tmp->type != PIPE)
		tmp = tmp->next;
    if(tmp && tmp->type == PIPE && tmp->next)
    {
        tmp = tmp->next;
        cmd->next = create_cmd_list(tmp);
    }
    else 
        cmd->next = NULL;
    return (cmd);
}

void    free_cmd_list(t_cmds **cmd_list)
{
    t_cmds  *tmp;
    int i;

    tmp = *cmd_list;
    while(tmp)
    {
        i = 0;
        free_redirs(&(tmp->redirs));
        while(tmp->argv[i])
        {
            free(tmp->argv[i]);
            i++;
        }
        free(tmp->argv);
        *cmd_list = tmp->next;
        free(tmp);
        tmp = *cmd_list;
    }
}