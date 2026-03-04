#include "minishell.h"

int main(int ac, char **av, char **envp)
{
    char    *input;
    t_envp  *my_env = NULL; 

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
            
            // Artık burada input'u kendi parser fonksiyonlarına göndereceksin.
            // Örnek akış şu şekilde olacak:
            // 1. Tokenize et
            // 2. Parse et (ve redirleri ayarla)
            // 3. Execute et
            
        }
        free(input);
    }
    
    free_envp_list(&my_env);
    
    return (0);
}