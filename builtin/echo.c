#include "builtin.h"

int echo_builtin(t_cmds *cmd)
{
    int i;
    int nw_line;
    
    i = 1;
    nw_line = 1;
    
    while(cmd->argv[i] && ft_strcmp(cmd->argv[i], "-n") == 0)
    {
        nw_line = 0;
        i++;
    }
    while(cmd->argv[i])
    {
        printf("%s", cmd->argv[i]);
        if(cmd->argv[i + 1])
            printf(" ");
        i++;
    }
    if(nw_line)
        printf("\n");
    return (0);
}