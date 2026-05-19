/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kagdas <kagdas@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 11:51:31 by kagdas            #+#    #+#             */
/*   Updated: 2026/05/19 12:18:21 by kagdas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static void	print_eof_warning(int line_count, char *delimiter)
{
	ft_putstr_fd("minishell: warning: here-document at line ", 2);
	ft_putnbr_fd(line_count, 2);
	ft_putstr_fd(" delimited by end-of-file (wanted `", 2);
	ft_putstr_fd(delimiter, 2);
	ft_putstr_fd("')\n", 2);
}

void	read_heredoc(char *delimiter, int write_fd, t_cmds **cmd, t_envp **env)
{
	char	*line;
	int		line_count;

	line_count = 1;
	while (1)
	{
		line = readline("> ");
		line_count++;
		if (!line)
		{
			print_eof_warning(line_count, delimiter);
			break ;
		}
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		write(write_fd, line, ft_strlen(line));
		write(write_fd, "\n", 1);
		free(line);
	}
	close(write_fd);
	free_all(cmd, env);
	exit(0);
}

static int	wait_heredoc_parent(pid_t pid, int *fd)
{
	int	status;

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	close(fd[1]);
	waitpid(pid, &status, 0);
	set_signals_interactive();
	if (WIFEXITED(status) && WEXITSTATUS(status) == 130)
	{
		close(fd[0]);
		return (-1);
	}
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		close(fd[0]);
		return (-1);
	}
	return (0);
}

static int	handle_heredoc(t_redirs *redir, t_cmds **cmd, t_envp **env)
{
	int		fd[2];
	pid_t	pid;

	if (!redir || !redir->target)
		return (-1);
	if (pipe(fd) < 0)
	{
		perror("pipe");
		return (-1);
	}
	pid = fork();
	if (pid < 0)
		return (perror("fork"), close(fd[0]), close(fd[1]), -1);
	if (pid == 0)
	{
		set_signals_heredoc();
		close(fd[0]);
		read_heredoc(redir->target, fd[1], cmd, env);
	}
	if (wait_heredoc_parent(pid, fd) < 0)
		return (-1);
	redir->fd = fd[0];
	return (0);
}

int	prepare_heredocs(t_cmds **cmd, t_envp **env)
{
	t_redirs	*redir;
	t_cmds		*tmp;

	tmp = *cmd;
	while (tmp)
	{
		redir = tmp->redirs;
		while (redir)
		{
			if (redir->type == HEREDOC)
			{
				if (redir->fd != -1)
				{
					close(redir->fd);
					redir->fd = -1;
				}
				if (handle_heredoc(redir, cmd, env) < 0)
					return (-1);
			}
			redir = redir->next;
		}
		tmp = tmp->next;
	}
	return (0);
}
