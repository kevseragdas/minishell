#include "execute.h"

int run_parent(t_cmds **cmd, t_envp **env)
{
    int backup_stdin;
    int backup_stdout;
    int status;  // for exit status

    backup_stdin = dup(STDIN_FILENO);
    backup_stdout = dup(STDOUT_FILENO);
    if(redirections(*cmd) < 0)
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
    pid_t   pid;
    int status;

    pid = fork();
    if(pid < 0)
    {
        perror("fork");
        return (1);
    }
    else if (pid == 0) // for child process
    {
        if(redirections(*cmd) < 0)
            exit(1);
        exec_external(*cmd, *env);
        perror("minishell");
        exit(1);
    }
    else //for parent process
    {
        waitpid(pid, &status, 0);

        if (WIFEXITED(status)) // normal exit
            return (WEXITSTATUS(status));
        else if (WIFSIGNALED(status)) // sinyal ile öldü
            return (128 + WTERMSIG(status));
    }
    return (1);
}

int execute_single(t_cmds **cmd, t_envp **env)
{
    int status;

    if(is_builtin((*cmd)->argv[0]))
        status = run_parent(cmd, env);
    else
        status = run_child(cmd, env);
    return (status);
}