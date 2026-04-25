#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>

# include "libft/libft.h"  
# include "parse/parse.h"
# include "builtin/builtin.h"
# include "execute/execute.h"

void	set_signals_interactive(void);

#endif