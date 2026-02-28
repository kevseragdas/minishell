#ifndef EXECUTE_H
#define EXECUTE_H

#include "minishell.h"
#include <fcntl.h>

typedef struct s_exit_status{
    int exit_status;
} t_exit_status ;


int exec_builtin(t_cmds **cmd, t_envp **env, int is_parent);


#endif