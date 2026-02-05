#include "builtin.h"

int env_builtin(t_cmds *cmd, t_envp *env_list)
{
    t_envp *tmp;

    if(cmd->argv[1])
    {
        write(2, "env: ", 5);
        write(2, cmd->argv[1], ft_strlen(cmd->argv[1]));
        write(2, ": No such file or directory\n", 28);
        return (127);
    }    
    tmp = env_list;
    while(tmp)
    {
        if(tmp->key && tmp->value)
            printf("%s=%s\n", tmp->key, tmp->value);
        tmp = tmp->next;
    }
    return (0);
}
