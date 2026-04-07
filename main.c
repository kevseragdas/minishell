#include "minishell.h"

int main(int ac, char **av, char **envp)
{
    char    *input;
    t_envp  *my_env = NULL;
    t_cmds *cmd;
    t_tokens *tokens;
    int status = 0; // 1. DEĞİŞİKLİK: Başlangıç çıkış kodunu 0 yapıyoruz

    (void)ac; (void)av;

    get_envp(&my_env, envp);
    set_signals_interactive();

    while (1)
    {
        input = readline("minishell$ ");
        
        if (!input)
        {
            // 2. DEĞİŞİKLİK: Sadece interaktif moddaysa "exit" yazdır
            // Tester komut yolladığında (non-interactive) Bash ekrana "exit" yazmaz!
            if (isatty(STDIN_FILENO))
                printf("exit\n"); 
            break;
        }

        if (ft_strlen(input) > 0)
        {
            add_history(input);

            tokens = lexer(input);
            check_token_syntax(&tokens);
            cmd = create_cmd_list(tokens);
            free_token_list(&tokens);
            
            // 3. DEĞİŞİKLİK: Çalıştırılan komutun dönüş kodunu status'e kaydet
            status = execute(&cmd, &my_env);
            
            free_cmd_list(&cmd);
        }
        free(input);
    }
    
    free_envp_list(&my_env);
    
    // 4. DEĞİŞİKLİK: Her zaman 0 değil, elimizdeki son durumu (status) döndür
    return (status);
}