/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kagdas <kagdas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 11:52:56 by kagdas            #+#    #+#             */
/*   Updated: 2026/05/19 11:52:57 by kagdas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "../libft/libft.h"
# include "../builtin/builtin.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <stdlib.h>

typedef enum s_token_type
{
	WORD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	HEREDOC
}	t_token_type;

typedef struct s_tokens
{
	t_token_type		type;
	char				*value;
	struct s_tokens		*prev;
	struct s_tokens		*next;
}	t_tokens;

typedef struct s_envp	t_envp;

void		free_token_list(t_tokens **tokens);
void		quote_check(char c, char	*quote);
int			check_token_syntax(t_tokens **token);
int			is_sep(char c);
t_tokens	*lexer(char *input);

typedef struct s_redirs
{
	t_token_type		type;
	char				*target;
	int					fd;
	struct s_redirs		*next;
}	t_redirs;

typedef struct s_cmds
{
	char			**argv;
	t_redirs		*redirs;
	struct s_cmds	*next;
	struct s_cmds	*prev;
}	t_cmds;

void		find_redirs(t_cmds **cmd, t_tokens *tmp);
void		free_redirs(t_redirs **redir);
void		free_cmd_list(t_cmds **cmd_list);
t_cmds		*create_cmd_list(t_tokens *tmp);
void		expand_tokens(t_tokens *tokens, t_envp *env, int last_status);
void		skip_spaces(char *input, int *i);
void		free_all(t_cmds **cmd, t_envp **env);
int			skip_escaped_char(char *s, int *i, char quote);

#endif