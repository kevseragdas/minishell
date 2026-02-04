#include "minishell.h"

int get_env_len(char **envp)
{
    int i;

    i = 0;
    while (envp && envp[i])
        i++;
    return (i);
}

char **copy_env(char **envp)
{
    char    **new_env;
    int     i;

    i = 0;
    new_env = malloc(sizeof(char *) * (get_env_len(envp) + 1));
    if (!new_env)
        return (NULL);
    while (envp[i])
    {
        new_env[i] = ft_strdup(envp[i]);
        i++;
    }
    new_env[i] = NULL;
    return (new_env);
}

// Environment içinde aranan değişkenin değerini döndürür
// Örn: get_env_value("USER", my_env) -> "kevseragdas" döner
char *get_env_value(char *var_name, char **env)
{
    int     i;
    int     len;
    char    *tmp_val;

    i = 0;
    len = ft_strlen(var_name);
    while (env[i])
    {
        // "VAR=" ile başlıyor mu kontrolü
        if (ft_strncmp(env[i], var_name, len) == 0 && env[i][len] == '=')
            return (env[i] + len + 1); // Eşittirden sonraki kısmı döndür
        i++;
    }
    return (NULL);
}