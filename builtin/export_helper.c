#include "builtin.h"

char    **find_env_arr(t_envp **env)
{
    int len;
    int i;
    t_envp  *tmp;
    char    **env_arr;

    i = 0;
    len = 0;
    tmp = *env;
    while(tmp)
    {
        len++;
        tmp = tmp->next;
    }
    env_arr = malloc(sizeof(char *) * (len + 1));
    tmp = *env;
    while(tmp)
    {
        env_arr[i] = ft_strdup(tmp->key);
        i++;
        tmp = tmp->next; 
    }
    env_arr[i] = NULL;
    return (env_arr);
}

char    **sort_env_arr(t_envp **env)
{
    int i;
    int j;
    char    **env_arr;
    char *env_tmp;

    i = 0;
    env_arr = find_env_arr(env);
    while(env_arr[i])
    {
        j = i + 1;
        while(env_arr[j])
        {
            if(ft_strcmp(env_arr[i], env_arr[j]) > 0)
            {
                env_tmp = env_arr[i];
                env_arr[i] = env_arr[j];
                env_arr[j] = env_tmp;
            }
            j++;
        }
        i++;
    }
    return (env_arr);
}

void    print_sorted_envs(t_envp **env)
{
    char    **env_arr;
    t_envp  *tmp;
    int i;
    int len;

    len = 0;
    i = 0;
    env_arr = sort_env_arr(env);
    tmp = *env;
    while(tmp)
    {
        len++;
        tmp = tmp->next;
    }
    while(i < len)
    {
        tmp = *env;
        while(tmp)
        {
            if(!ft_strcmp(tmp->key, env_arr[i]))
            {
                if (tmp->value == NULL)
                    printf("declare -x %s\n", tmp->key);
                else if (tmp->value[0] == '\0')
                    printf("declare -x %s=\"\"\n", tmp->key);
                else
                    printf("declare -x %s=\"%s\"\n", tmp->key, tmp->value);
            }
            tmp = tmp->next;
        }
        i++;
    }
    i = 0;
    while(i < len)
        free(env_arr[i++]);
    free(env_arr);
}