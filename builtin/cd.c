#include "builtin.h"

void print_error(char *msg)
{
    write(2, msg, ft_strlen(msg));
}

void    add_oldpwd(t_envp **env, char *cwd1)
{
    t_envp  *oldpwd;
    t_envp *tmp;

    oldpwd = malloc(sizeof(t_envp));
    if(!oldpwd)
        return ;
    oldpwd->key = ft_strdup("OLDPWD");
    oldpwd->value = ft_strdup(cwd1);
    oldpwd->next = NULL;
    tmp = *env;
    if(!(*env))
    {
        *env = oldpwd;
        return ;
    }
    while(tmp->next)
        tmp = tmp->next;
    tmp->next = oldpwd;
}

void    update_pwds(t_envp **env, char *cwd1, char *cwd2)
{
    t_envp  *tmp;
    int check_oldpwd;

    check_oldpwd = 0;
    tmp = *env;
    while(tmp)
    {
        if(ft_strcmp(tmp->key, "OLDPWD") == 0)
        {
            free(tmp->value);
            tmp->value = ft_strdup(cwd1);
            check_oldpwd = 1;
        }
        else if(ft_strcmp(tmp->key, "PWD") == 0)
        {
            free(tmp->value);
            tmp->value = ft_strdup(cwd2);
        }
        tmp = tmp->next;
    }
    if(check_oldpwd == 0)
        add_oldpwd(env, cwd1);
}

int cd_builtin(t_cmds *cmd, t_envp **env)
{
    char    cwd1[4096];
    char    cwd2[4096];

    if(!cmd->argv[1] || cmd->argv[2])
    {
        print_error("cd: invalid number of arguments\n");
        return (1);
    }
    if(getcwd(cwd1, sizeof(cwd1)) == NULL)
    {
        print_error("cd: getcwd() error\n");
        return (1);
    }
    if(chdir(cmd->argv[1]) != 0)
    {
        print_error("cd: no such file or directory\n");
        return (1);
    }
    if(getcwd(cwd2, sizeof(cwd2)) == NULL)
    {
        print_error("cd: getcwd() error\n");
        return (1);
    }
    update_pwds(env, cwd1, cwd2);
    return (0);
}