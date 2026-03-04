#include "execute.h"

int redir_in(t_redirs *redir)
{
    int fd;

    fd = open(redir->target, O_RDONLY);
    if (fd < 0)
    {
        perror(redir->target);
        return (-1);
    }
    if (dup2(fd, STDIN_FILENO) < 0)
    {
        perror("dup2");
        close(fd);
        return (-1);
    }
    close(fd);
    return (0);
}

int redirections(t_cmds *cmd)
{
    t_redirs    *redir;
    int status;

    redir = cmd->redirs;
    while(redir)
    {
        if(redir->type == REDIR_IN)
        {
            status = redir_in(redir);
        }
        else if (redir->type == REDIR_OUT)
        {

        }
        else if (redir->type == REDIR_APPEND)
        {

        }
        else if (redir->type == HEREDOC)
        {

        }
        if(status != 0)
            return (-1);
        redir = redir->next;
    }
    return (0);
}