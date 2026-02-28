#include "execute.h"

int run_parent(t_cmds **cmd,t_envp **env)
{
    int backup_stdin;
    int backup_stdout;
    int status;  // for exit status

    backup_stdin = dup(STDIN_FILENO);
    backup_stdout = dup(STDOUT_FILENO);
    if(redirections(cmd) < 0)
    {
        dup2(backup_stdin, STDIN_FILENO);
        dup2(backup_stdout, STDOUT_FILENO);
        close(backup_stdin);
        close(backup_stdout);
        return (1);
    }

    status = exec_builtin(cmd, env, 1);

    dup2(backup_stdin, STDIN_FILENO);
    dup2(backup_stdout, STDOUT_FILENO);
    close(backup_stdin);
    close(backup_stdout);

    return (status);
}

int run_child(t_cmds **cmd, t_envp **env)
{

}

int execute_single(t_cmds **cmd, t_envp **env)
{
    if(is_builtin((*cmd)->argv[0]))
        run_parent(cmd, env);
    else
        run_child(cmd, env);
}