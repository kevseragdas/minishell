#include "builtin.h"

//parent ve child ayrımını execution aşamasında handle etmen gerekiyor.

int check_exit_status(char *str, int is_parent, int *control)
{
    int i;

    i = 0;
    while(str[i])
    {
        if(!ft_isdigit(str[i]))
        {
            if (is_parent)
            {
                write(2, "exit\n", 5);
                write(2, "minishell: exit: ", 17);
                write(2, str, ft_strlen(str));
                write(2, ": numeric argument required\n", 28);
                *control = 1;
            }
            return (255);
        }
        i++;
    }
    return (0);
}

int exit_builtin(t_cmds **cmd, t_envp **env, int is_parent)
{
    int status;
    int i;
    int control;

    control = 0;
    status = 0;
    i = 0;
    if((*cmd)->argv[1])
    {
        status = check_exit_status((*cmd)->argv[1], is_parent, &control);
        if(status != 255)
            status = ft_atoi((*cmd)->argv[1]) % 256;
    }
    if (is_parent)
    {
        if(!control)
            write(2, "exit\n", 5);
        free_cmd_list(cmd);
        free_envp_list(env);
        exit(status);
    }
    return status;
}