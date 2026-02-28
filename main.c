#include "minishell.h"

// --- YARDIMCI FONKSİYONLAR ---

static int  is_var_char(char c)
{
    return (ft_isalnum(c) || c == '_');
}

char    *find_env_value(t_envp *env, char *key)
{
    size_t  len;

    if (!key || !env)
        return (NULL);
    len = ft_strlen(key);
    while (env)
    {
        if (ft_strncmp(env->key, key, len) == 0 
            && env->key[len] == '\0')
            return (env->value);
        env = env->next;
    }
    return (NULL);
}

int get_var_len(char *str)
{
    int i;

    i = 0;
    if (str[i] == '?') 
        return (1);
    if (ft_isdigit(str[i])) 
        return (1);
    while (str[i] && is_var_char(str[i]))
        i++;
    return (i);
}

static int  update_quote(int quote, char c)
{
    if (c == '\'' && quote != 2)
        return (quote == 0);
    if (c == '\"' && quote != 1)
        return ((quote == 0) * 2);
    return (quote);
}

static int  calc_len(char *str, t_envp *env)
{
    int     i;
    int     len;
    int     quote;
    char    *tmp;
    
    i = -1;
    len = 0;
    quote = 0;
    while (str[++i])
    {
        if ((str[i] == '\'' && quote != 2) || (str[i] == '\"' && quote != 1))
            quote = update_quote(quote, str[i]);
        else if (str[i] == '$' && quote != 1 && (is_var_char(str[i + 1]) || str[i + 1] == '?'))
        {
            tmp = ft_substr(str, i + 1, get_var_len(&str[i + 1]));
            if (find_env_value(env, tmp))
                len += ft_strlen(find_env_value(env, tmp));
            free(tmp);
            i += get_var_len(&str[i + 1]);
        }
        else
            len++;
    }
    return (len);
}

// --- ANA GENİŞLETME FONKSİYONU ---

char    *expand_str(char *str, t_envp *env)
{
    int     i = 0;
    int     j = 0;
    int     quote = 0;
    char    *res;
    char    *val;
    char    *tmp_key;

    int len = calc_len(str, env);
    res = malloc(sizeof(char) * (len + 1));
    if (!res) return (NULL);
    
    while (str[i])
    {
        if ((str[i] == '\'' && quote != 2) || (str[i] == '\"' && quote != 1))
            quote = update_quote(quote, str[i]);

        if (str[i] == '$' && quote != 1 && (is_var_char(str[i + 1]) || str[i + 1] == '?'))
        {
            int var_len = get_var_len(&str[i + 1]);
            tmp_key = ft_substr(str, i + 1, var_len);
            val = find_env_value(env, tmp_key);
            
            if (val)
            {
                ft_strlcpy(&res[j], val, ft_strlen(val) + 1);
                j += ft_strlen(val);
            }
            free(tmp_key);
            i += var_len + 1;
        }
        else
        {
            if (!((str[i] == '\'' && quote != 2) || (str[i] == '\"' && quote != 1)))
                res[j++] = str[i];
            i++;
        }
    }
    res[j] = '\0';
    return (res);
}

// --- MAIN FONKSİYONU ---

int main(int ac, char **av, char **envp)
{
    char    *input;
    char    *expanded_input;
    t_envp  *my_env = NULL; 

    (void)ac; (void)av;

    get_envp(&my_env, envp);

    while (1)
    {
        input = readline("minishell$ ");
        if (!input)
            break;
        
        if (ft_strlen(input) > 0)
        {
            add_history(input);
            
            expanded_input = expand_str(input, my_env);
            
            printf("EXPANDED: [%s]\n", expanded_input);
            
            free(expanded_input);
        }
        free(input);
    }
    
    free_envp_list(&my_env);
    
    return (0);
}