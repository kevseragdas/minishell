#include "builtin.h"

//parent ve child ayrımını execution aşamasında handle etmen gerekiyor.
int exit_builtin(t_cmds *cmd)
{
    if(cmd->argv[1])
    {
        printf("exit : too many arguments!\n");
        return (1);
    }
    exit(0);
}