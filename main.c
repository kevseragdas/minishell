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

/////////////////////////////////////////////////////////////////////77

#include <stdio.h>

void print_redirs(t_redirs *redirs)
{
    while (redirs)
    {
        printf("    Redir type: %d\n", redirs->type);
        if (redirs->target)
            printf("    Target: %s\n", redirs->target);
        printf("    FD: %d\n", redirs->fd);
        redirs = redirs->next;
    }
}

void print_cmds(t_cmds *cmds)
{
    int i;

    while (cmds)
    {
        printf("Command:\n");

        // argv
        i = 0;
        if (cmds->argv)
        {
            printf("  argv: ");
            while (cmds->argv[i])
            {
                printf("%s ", cmds->argv[i]);
                i++;
            }
            printf("\n");
        }

        // fds
        printf("  in_fd: %d\n", cmds->in_fd);
        printf("  out_fd: %d\n", cmds->out_fd);

        // redirs
        if (cmds->redirs)
        {
            printf("  Redirections:\n");
            print_redirs(cmds->redirs);
        }

        printf("----\n");
        cmds = cmds->next;
    }
}


/////////////////////////////////////////////////////////77


int main(int ac, char **av, char **envp)
{
    char        *input;
    t_tokens    *tokens;
    t_cmds      *cmds;

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
                //print_tokens(tokens);
                check_token_syntax(&tokens);
                cmds = create_cmd_list(tokens);
                free_token_list(&tokens);
                ///print_cmds(cmds);
            }
        }
        free(input);
    }

    return (0);
}