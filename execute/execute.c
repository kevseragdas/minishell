#include "execute.h"

int execute(t_cmds **cmd, t_envp **env)
{
    if(((*cmd)->next))
        execute_non_single(cmd, env);
    else
        execute_single(cmd, env);
    free_envp_list(env);
    free_cmd_list(cmd);
}