#include "execute.h"

int	exec_builtin(t_cmds **cmd, t_envp **env, int is_parent)
{
	if (!cmd || !*cmd || !(*cmd)->argv || !(*cmd)->argv[0])
		return (0);
	if (!ft_strcmp((*cmd)->argv[0], "echo"))
		return (echo_builtin(*cmd), 0);
	else if (!ft_strcmp((*cmd)->argv[0], "cd"))
		return (cd_builtin(*cmd, env));
	else if (!ft_strcmp((*cmd)->argv[0], "pwd"))
		return (pwd_builtin(), 0);
	else if (!ft_strcmp((*cmd)->argv[0], "export"))
		return (export_builtin(*cmd, env));
	else if (!ft_strcmp((*cmd)->argv[0], "unset"))
		return (unset_builtin(*cmd, env));
	else if (!ft_strcmp((*cmd)->argv[0], "env"))
		return (env_builtin(*cmd, *env), 0);
	else if (!ft_strcmp((*cmd)->argv[0], "exit"))
		return (exit_builtin(cmd, env, is_parent));
	return (0);
}
