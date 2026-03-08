#include "execute.h"

int execute_non_single(t_cmds *cmd, t_envp **env)
{
    int fd[2];
    int prev_fd_in;
    pid_t pid;
    pid_t last_pid;
    int status;

    prev_fd_in = STDIN_FILENO;
    while(cmd)
    {
        if(cmd->next && pipe(fd))
        {
            perror("pipe");
            return (1);
        }
        pid = fork();
        if(pid < 0)
        {
            perror("fork");
            return (1);
        }
        else if(pid == 0)
        {
            dup2(prev_fd_in, STDIN_FILENO);
            if(cmd->next)
                dup2(fd[1], STDOUT_FILENO);
            ///////////////
            if (prev_fd_in != STDIN_FILENO)
                close(prev_fd_in);
            if (cmd->next)
            {
                close(fd[0]);
                close(fd[1]);
            }
            //////////////
            exec_external(cmd, *env);
            exit (1);
        }
        else //parent process
        {   
            if (prev_fd_in != STDIN_FILENO)
                close(prev_fd_in);
            if (cmd->next)
                close(fd[1]);
            
            if (cmd->next)
                prev_fd_in = fd[0];
            
            last_pid = pid;
        }
        cmd = cmd->next;
    }                
    while ((pid = wait(&status)) > 0)
    {
        if (pid == last_pid) // sadece son child’ın status’ünü sakla
        {
            if (WIFEXITED(status))
                return WEXITSTATUS(status);
            else if (WIFSIGNALED(status))
                return 128 + WTERMSIG(status);
        }
    }
    return 1;
}