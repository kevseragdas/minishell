#include "minishell.h"

int main(int ac, char **arg, char **envp)
{
	(void)ac;
	char *input;
    char *path = "/bin/ls";
	int num = 0;
	int *new;
	int i = 0;
    
	
		input = readline("minishell$ ");
		//execv(path, &input);	
		new = len_of_word(input);
		while(new[i])
		{
			printf("%d\n", new[i]);
			i++;
		}
    return (0);
}
//while (input[i] == ' ' || input[i] == '\t')
//			i++;
//		len = i;
//		while (input[i] && (input[i] != ' ' && input[i] != '\t'))
//		{
//			while (input[i] == ' ' || input[i] == '\t')
//				i++;
//			if (input[i] == '"' || input[i] == '\'')
//			{
//				i++;
//				while (input[i] != '"' && input[i] != '\'')
//					i++;
//				len = i - len;
//				length[j] = len;
//				j++;
//				i++;
//			}
//			else if(input[i] && (input[i] != ' ' && input[i] != '\t'))
//			{
//				while (input[i] && (input[i] != ' ' && input[i] != '\t'))
//					i++;
//				len = i - len;
//				length[j] = len;
//				j++;
//			}
//		}
//		length[j] = '\0';