#include "builtin.h"

int is_valid_identifier(char *arg)
{
    int j = 0;

    if (!arg || !arg[0])
        return (0);

    if (!(ft_isalpha(arg[0]) || arg[0] == '_'))
        return (0);

    while (arg[j] && arg[j] != '=')
    {
        if (!(ft_isalnum(arg[j]) || arg[j] == '_'))
            return (0);
        j++;
    }
    return (1); 
}



int  unset_free(t_envp **tmp)
{
    free((*tmp)->key);
    free((*tmp)->value);
    free(*tmp);
    return (0);
}

int unset_helper(char *argv, t_envp **env)
{
    t_envp  *tmp;
    t_envp  *pre_tmp;

    if(!*env)
        return (0);
    tmp = *env;
    if (ft_strcmp(argv, tmp->key) == 0)
    {
        *env = tmp->next;
        return (unset_free(&tmp));
    }
    pre_tmp = tmp;
    tmp = tmp->next;
    while(tmp)
    {
        if(ft_strcmp(argv, tmp->key) == 0)
        {
            pre_tmp->next = tmp->next;
            return (unset_free(&tmp));
        }
        pre_tmp = pre_tmp->next;
        tmp = pre_tmp->next;
    }
    return (0);
}

int unset_builtin(t_cmds *cmd, t_envp **env)
{
    int i;
    int cntrl;

    i = 1;
    cntrl = 0;
    while(cmd->argv[i])
    {
        if(!is_valid_identifier(cmd->argv[i]))
        {
            write(2, "unset: `", 8);
            write(2, cmd->argv[i], ft_strlen(cmd->argv[i]));
            write(2, "`: not a valid identifier\n", 26);
            return (1);
        }
        cntrl = unset_helper(cmd->argv[i], env);
        if(cntrl)
            return (1);
        i++;
    }
    return (0);
}

