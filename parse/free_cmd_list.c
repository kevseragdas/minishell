#include "parse.h"

void	free_cmd_list(t_cmds **cmd_list)
{
	t_cmds	*tmp;
	int		i;

	while (*cmd_list)
	{
		tmp = *cmd_list;
		i = 0;
		free_redirs(&(tmp->redirs));
		if (tmp->argv)
		{
			while (tmp->argv[i])
			{
				free(tmp->argv[i]);
				i++;
			}
			free(tmp->argv);
		}
		*cmd_list = tmp->next;
		free(tmp);
	}
}
