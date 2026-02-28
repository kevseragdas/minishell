#include "execute.c"

int exec_builtin(t_cmds **cmd, t_envp **env, int is_parent)
{
    if (!ft_strcmp((*cmd)->argv[0], "echo"))
        echo_builtin(cmd);
    if (!ft_strcmp((*cmd)->argv[0], "cd"))
        cd_builtin(cmd, env);
    if (!ft_strcmp((*cmd)->argv[0], "pwd"))
        pwd_builtin();
    if (!ft_strcmp((*cmd)->argv[0], "export"))
        export_builtin(cmd, env);
    if (!ft_strcmp((*cmd)->argv[0], "unset"))
        unset_builtin(cmd, env);
    if (!ft_strcmp((*cmd)->argv[0], "env"))
        env_builtin(cmd, *env);
    if (!ft_strcmp((*cmd)->argv[0], "exit"))
        exit_builtin(cmd, env, is_parent);
    return (0);
}