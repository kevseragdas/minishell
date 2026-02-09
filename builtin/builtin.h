#ifndef BUILTIN_H
#define BUILTIN_H

# include "../libft/libft.h" 
# include "../parse/parse.h"


typedef struct s_envp{
    char *key;
    char *value;
    struct s_envp *next;
} t_envp ;


char	*find_env_value(t_envp *env, char *key);
int ft_strcmp(const char *s1, const char *s2);
int  find_equal_sign(char *str);
int is_valid_identifier(char *arg);
void print_error(char *msg);
void    find_key_value(char *env_string, char **key, char **value);
void    get_envp(t_envp **env_head, char **envp);
void    free_envp_list(t_envp **envp);
int is_builtin(char *cmd);
int pwd_builtin(void);
int echo_builtin(t_cmds *cmd);
int env_builtin(t_cmds *cmd, t_envp *env_list);
int exit_builtin(t_cmds *cmd);
int cd_builtin(t_cmds *cmd, t_envp **env);
int unset_builtin(t_cmds *cmd, t_envp **env);
int export_builtin(t_cmds *cmd, t_envp **env);

#endif