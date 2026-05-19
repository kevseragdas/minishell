/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kagdas <kagdas@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 11:51:45 by kagdas            #+#    #+#             */
/*   Updated: 2026/05/19 12:25:17 by kagdas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
void	set_signals_heredoc(void);
extern volatile sig_atomic_t	g_signal;
#endif
