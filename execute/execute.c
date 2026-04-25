#include "execute.h"

int	execute(t_cmds **cmd, t_envp **env)
{
	if (!cmd || !*cmd)
		return (0);
	if (prepare_heredocs(*cmd) < 0)
		return (130);
	if ((*cmd)->next)
		return (execute_non_single(*cmd, env));
	return (execute_single(cmd, env));
}
