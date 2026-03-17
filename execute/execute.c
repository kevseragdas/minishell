#include "execute.h"

int execute(t_cmds **cmd, t_envp **env)
{
    if(((*cmd)->next))
        return (execute_non_single(*cmd, env));
    else
        return (execute_single(cmd, env));
}
