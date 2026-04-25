#ifndef EXECUTE_H
# define EXECUTE_H

# include "../builtin/builtin.h"
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <signal.h>
# include <errno.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

int		exec_builtin(t_cmds **cmd, t_envp **env, int is_parent);
int		exec_external(t_cmds *cmd, t_envp *env);
void	run_builtin_in_child(t_cmds *cmd, t_envp **env);
void	setup_pipe_input(int prev_fd);
void	setup_pipe_output(t_cmds *cmd, int fd[2]);
int		create_child(t_cmds *cmd, t_envp **env, int prev_fd, int fd[2]);
int		execute_non_single(t_cmds *cmd, t_envp **env);
int		execute_single(t_cmds **cmd, t_envp **env);
int		redirections(t_cmds *cmd);
int		execute(t_cmds **cmd, t_envp **env);
int		is_builtin(char *cmd_name);
int		find_path(char *argv_0, char **path, t_envp *env);
void	print_command_error(const char *cmd, int error_type);
void	free_2d_arr(char **arr);
int		handle_heredoc(t_redirs *redir);
void	set_signals_interactive(void);
void	set_signals_executing(void);
int		prepare_heredocs(t_cmds *cmd);

#endif