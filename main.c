#include "minishell.h"

static int	handle_input(char *input, t_envp **my_env, int *last_status)
{
	t_tokens	*tokens;
	t_cmds		*cmd;
	int			syntax_status;

	tokens = lexer(input);
	if (!tokens)
		return (2);
	syntax_status = check_token_syntax(&tokens);
	if (syntax_status != 0)
		return (syntax_status);
	expand_tokens(tokens, *my_env, *last_status);
	cmd = create_cmd_list(tokens);
	free_token_list(&tokens);
	if (!cmd)
		return (1);
	*last_status = execute(&cmd, my_env);
	free_cmd_list(&cmd);
	return (*last_status);
}

static void	handle_signal_status(int *last_status)
{
	if (g_signal == SIGINT)
	{
		*last_status = 130;
		g_signal = 0;
	}
}

static void	process_input(char *input, t_envp **my_env, int *last_status)
{
	if (input[0] != '\0')
	{
		add_history(input);
		*last_status = handle_input(input, my_env, last_status);
	}
}

static int	minishell_loop(t_envp **my_env)
{
	char	*input;
	int		last_status;

	last_status = 0;
	while (1)
	{
		input = readline("minishell$ ");
		handle_signal_status(&last_status);
		if (!input)
			break ;
		process_input(input, my_env, &last_status);
		free(input);
	}
	return (last_status);
}

int	main(int ac, char **av, char **envp)
{
	t_envp	*my_env;
	int		last_status;

	(void)ac;
	(void)av;
	my_env = NULL;
	get_envp(&my_env, envp);
	set_signals_interactive();
	last_status = minishell_loop(&my_env);
	free_envp_list(&my_env);
	if (isatty(STDIN_FILENO))
		printf("exit\n");
	return (last_status);
}
