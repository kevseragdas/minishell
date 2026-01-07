#include "minishell.h"

int main(int ac, char **arg, char **envp)
{
	(void)ac;
	char *input;
    char *path = "/bin/ls";
	int num = 0;
	char **new;
	int i = 0;
    
	
		input = readline("minishell$ ");
		//execv(path, &input);	
		num = num_of_word(input);
		printf("%d\n",num);
		new = word_count(input);
		while(new[i])
		{
			printf("%s\n", new[i]);
			i++;
		}
    return (1);
}