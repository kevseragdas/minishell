#include "builtin.h"

//parent ve child ayrımını execution aşamasında handle etmen gerekiyor.
int exit_builtin(t_cmds *cmd)
{
    if(cmd->argv[1])
    {
        write(2, "exit: too many arguments\n", 25);
        return (1);
    }
    exit(0);
}