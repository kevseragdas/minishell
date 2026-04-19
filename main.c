#include "minishell.h"

int	main(int ac, char **av, char **envp)
{
	char		*input;
	t_envp		*my_env;
	t_cmds		*cmd;
	t_tokens	*tokens;
	int			last_status;
	int			syntax_status;

	(void)ac;
	(void)av;
	my_env = NULL;
	last_status = 0;
	get_envp(&my_env, envp);
	set_signals_interactive();
	while (1)
	{
		input = readline("minishell$ ");
		if (!input)
		{
			if (isatty(STDIN_FILENO))
				printf("exit\n");
			break ;
		}
		if (input[0] == '\0')
		{
			free(input);
			continue ;
		}
		add_history(input);
		tokens = lexer(input);
		free(input);
		if (!tokens)
		{
			last_status = 2;
			continue ;
		}
		syntax_status = check_token_syntax(&tokens);
		if (syntax_status != 0)
		{
			last_status = syntax_status;
			continue ;
		}
		expand_tokens(tokens, my_env, last_status);
		cmd = create_cmd_list(tokens);
		free_token_list(&tokens);
		if (!cmd)
		{
			last_status = 1;
			continue ;
		}
		last_status = execute(&cmd, &my_env);
		free_cmd_list(&cmd);
	}
	free_envp_list(&my_env);
	return (last_status);
}