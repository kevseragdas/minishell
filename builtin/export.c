#include "builtin.h"

void new_key_value(t_envp **env, char **key, char **value)
{
    t_envp *new_env;
    t_envp  *tmp;

    new_env = malloc(sizeof(t_envp));
    if(!new_env)
        return ;
    new_env->key = ft_strdup(*key);
    new_env->value = ft_strdup(*value);
    new_env->next = NULL;
    tmp = *env;
    if(tmp == NULL)
    {
        *env = new_env;
        free(*key);
        free(*value);
        return ;
    }
    while(tmp->next)
        tmp = tmp->next;
    tmp->next = new_env;
    free(*key);
    free(*value);
}

void is_there_key(char *argv, t_envp **env)
{
    char *key;
    char *value;
    t_envp *tmp;

    tmp = *env;
    find_key_value(argv, &key, &value);
    while(tmp)
    {
        if(ft_strcmp(tmp->key, key) == 0)
        {
            if (ft_strchr(argv, '='))
            {
                free(tmp->value);
                tmp->value = ft_strdup(value);
            }
            free(key);
            free(value);
            return ;
        }
        tmp = tmp->next;
    }

    new_key_value(env, &key, &value);
}

int export_builtin(t_cmds *cmd, t_envp **env)
{
    int i;

    i = 1;
    if(!cmd->argv[1])
    {
        print_sorted_envs(env);
        return (0);
    }
    while(cmd->argv[i])
    {
        if(!is_valid_identifier(cmd->argv[i]))
        {
            write(2, "export: `", 9);
            write(2, cmd->argv[i], ft_strlen(cmd->argv[i]));
            write(2, "`: not a valid identifier\n", 26);
            return (1);
        }
        is_there_key(cmd->argv[i], env);
        i++;
    }
    return (0);
}