#include "builtin.h"

int  find_equal_sign(char *str)
{
    int  i;

    i = 0;
    while(str[i] && str[i] != '=')
        i++;
    return (i);
}

void    find_key_value(char *env_string, char **key, char **value)
{
    int equal_indx;

    equal_indx = find_equal_sign(env_string);
    if (env_string[equal_indx] != '=')
    {
        *key = ft_strdup(env_string);
        *value = ft_strdup("");
        return;
    }

    *key = malloc(equal_indx + 1);
    *value = malloc(ft_strlen(env_string) - equal_indx + 1);
    if(!*value)
        return ;
    if (!*key || !*value)
    {
        free(*key);
        free(*value);
        return;
    }

    ft_strlcpy(*key, env_string, equal_indx + 1);
    ft_strlcpy(*value, env_string + equal_indx + 1, ft_strlen(env_string) - equal_indx + 1);
}

t_envp    *get_envp_helper(char *env_string)
{
    t_envp *res;
    char *key;
    char *value;
    
    if(!env_string)
        return (NULL);
    key = NULL;
    value = NULL;
    res = malloc(sizeof(t_envp));
    if(!res)
        return (NULL);
    find_key_value(env_string, &key, &value);
    res->key = key;
    res->value = value;
    res->next = NULL;
    return (res);
}

void    get_envp(t_envp **env_head, char **envp)
{
    t_envp  *tail;
    t_envp  *new;
    t_envp  *head;
    int i;

    i = 0;
    tail = NULL;
    head = NULL;
    while(envp[i])
    {
        new = get_envp_helper(envp[i]);
        if(!new)
        {
            free_envp_list(&head);
            return ;
        }
        if(head == NULL)
        {
            head = new;
            tail = head;
        }
        else
        {
            tail->next = new;
            tail = new;
        }
        i++;
    }
    *env_head = head;
}

void    free_envp_list(t_envp **envp_list)
{
    t_envp  *tmp;

    tmp = *envp_list;
    while(tmp)
    {
        free(tmp->key);
        free(tmp->value);
        *envp_list = tmp->next;
        free(tmp);
        tmp = *envp_list;
    }
}