#include "execute.h"

void free_2d_arr(char **arr)
{
    int i = 0;

    if (!arr)
        return ;
    while (arr[i])
    {
        free(arr[i]);   
        i++;
    }
    free(arr);          
}

void print_command_error(const char *cmd, int error_type)
{
    if (error_type == 127) // command not found
    {
        write(2, "minishell: ", 11);
        write(2, cmd, ft_strlen(cmd));
        write(2, ": command not found\n", 21);
    }
    else if (error_type == 126) // permission denied
    {
        write(2, "minishell: ", 11);
        write(2, cmd, ft_strlen(cmd));
        write(2, ": Permission denied\n", 21);
    }
}

int check_access(char **paths, char **path, char *argv_0)
{
    int i;
    int f_ok;
    int x_ok;
    char *tmp_str;

    i = 0;
    f_ok = 1;
    while(paths[i])
    {
        tmp_str = ft_strjoin(paths[i], "/");
        *path = ft_strjoin(tmp_str, argv_0);
        free(tmp_str);
        if(f_ok)
            f_ok = access(*path, F_OK);
        x_ok = access(*path, X_OK);
        if(x_ok == 0)
            return (0);
        free(*path);
        i++;
    }
    if(!f_ok)
        return (126);
    return (127);
}

int find_path(char *argv_0, char **path, t_envp *env)
{
    t_envp *tmp;
    char **paths;
    int status;

    if(ft_strchr(argv_0, '/'))
    {
        if (access(argv_0, F_OK) != 0)
            return (127);
        if (access(argv_0, X_OK) != 0)
            return (126);
        *path = ft_strdup(argv_0);
        return (0);
    }
    tmp = env;
    while(tmp && ft_strcmp(tmp->key, "PATH"))
        tmp = tmp->next;
    if(!tmp)
        return(127);
    paths = ft_split(tmp->value, ':');
    status = check_access(paths, path, argv_0);
    free_2d_arr(paths);
    return (status);
}

int exec_external(t_cmds *cmd, t_envp *env)
{
    char *path;
    int status;
    char **arr_env;

    status = find_path(cmd->argv[0], &path, env);
    if(status)
    {
        print_command_error(cmd->argv[0], status);
        exit(status);
    }
    if (is_directory(path))
    {
        write(2, "minishell: ", 11);
        write(2, path, ft_strlen(path));
        write(2, ": Is a directory\n", 17);
        free(path);
        exit(126);
    }
    arr_env = get_arr_env(env);
    execve(path, cmd->argv, arr_env);

    free(path);
    free_2d_arr(arr_env);
    errno_handler();
}