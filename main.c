#include "minishell.h"

#include "minishell.h"

void print_tokens(t_tokens *tokens)
{
    t_tokens *current;
    int i;

    current = tokens;
    i = 0;
    printf("\n--- TOKEN LIST ---\n");
    while (current != NULL)
    {
        printf("Token [%d]:\n", i);
        printf("  Value: [%s]\n", current->value);
        
        // Token tipini anlamlandırmak için basit bir switch veya if yapısı
        printf("  Type:  ");
        if (current->type == 0) // Örnek: 0 = WORD
            printf("WORD\n");
        else if (current->type == 1) // Örnek: 1 = PIPE
            printf("PIPE\n");
        else
            printf("%d\n", current->type); // Tanımlı değilse sayısal değerini bas
            
        printf("------------------\n");
        current = current->next;
        i++;
    }
    printf("--- END OF LIST ---\n\n");
}
int main(int ac, char **av, char **envp)
{
    char        *input;
    t_tokens    *tokens;

    (void)ac; (void)av; (void)envp;
    while (1)
    {
        input = readline("minishell$ ");
        if (!input) 
            break;
        if (input[0] != '\0')
        {
            add_history(input);
            tokens = lexer(input);
            if (tokens)
            {
                print_tokens(tokens);
                free_token_list(&tokens);
            }
        }
        free(input);
    }
    return (0);
}