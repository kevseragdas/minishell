#include "execute.h"

int is_directory(char *path)
{
    struct stat st;

    if (stat(path, &st) == -1)
        return (0);
    return (S_ISDIR(st.st_mode));
}

void    errno_handler(void)
{

    if (errno == EACCES)
    {
        perror("minishell");
        exit(126);
    }
    else if (errno == ENOENT)
    {
        perror("minishell");
        exit(127);
    }
    else if (errno == EISDIR)
    {
        perror("minishell");
        exit(126);
    }
    else
    {
        perror("minishell");
        exit(1);
    }
}