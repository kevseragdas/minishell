#ifndef EXECUTE_H
#define EXECUTE_H

#include "../builtin/builtin.h"
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>

typedef struct s_exit_status{
    int exit_status;
} t_exit_status ;


int exec_builtin(t_cmds **cmd, t_envp **env, int is_parent);
int exec_external(t_cmds *cmd, t_envp *env);
int execute_non_single(t_cmds *cmd, t_envp **env);
int execute_single(t_cmds **cmd, t_envp **env);
int redirections(t_cmds *cmd);
int is_directory(char *path);
void    errno_handler(void);
int execute(t_cmds **cmd, t_envp **env);

#endif