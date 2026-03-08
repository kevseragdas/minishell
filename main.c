#include "minishell.h"

int main(int ac, char **av, char **envp)
{
    char    *input;
    t_envp  *my_env = NULL;
    t_cmds *cmd;
    t_tokens *tokens;
    int status;

    (void)ac; (void)av;

    // Ortam değişkenlerini (environment variables) listeye alıyoruz
    get_envp(&my_env, envp);

    // DÖNGÜ BAŞLAMADAN ÖNCE SİNYALLERİ İNTERAKTİF MODA ALIYORUZ
    set_signals_interactive();

    while (1)
    {
        input = readline("minishell$ ");
        
        // Ctrl+D (EOF) basılırsa readline NULL döndürür
        if (!input)
        {
            printf("exit\n"); // Bash'teki gibi ekrana exit yazdırıp çıkıyoruz
            break;
        }

        if (ft_strlen(input) > 0)
        {
            add_history(input);

            tokens = lexer(input);
            check_token_syntax(&tokens);
            cmd = create_cmd_list(tokens);
            free_token_list(&tokens);
            
            execute(&cmd, &my_env);
            
            
            // Artık burada input'u kendi parser fonksiyonlarına göndereceksin.
            // Örnek akış şu şekilde olacak:
            // 1. Tokenize et
            // 2. Parse et (ve redirleri ayarla)
            // 3. Execute et

            
            free_cmd_list(&cmd);
            
        }
        free(input);
    }
    
    free_envp_list(&my_env);
    
    return (0);
}