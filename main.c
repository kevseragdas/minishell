#include "minishell.h"

int main(int ac, char **arg, char **envp)
{
	(void)ac;
	char *input;
    char *path = "/bin/ls";
	char **new;
	int i = 0;
	int j = 0;
	int num = 0;
    char *cleaned_str = NULL;
	
		input = readline("minishell$ ");
		//execv(path, &input);	
		j = get_word_len(input, 0);
		if(is_empty(input))
		{
			printf("empty\n");
			return (0);
		}
		if (!is_one_quote(input, '"') || !is_one_quote(input, '\''))
		{
			printf("error: unclosed double quote\n");
			return (0);
		}
		num = num_of_word(input);
		printf("num: %d\n",num);                                                                                                                                                     
		new = word_count(input);
		while(new[i])
		{
			char *cleaned_str = del_quotes(new[i]);
			printf("%s\n", cleaned_str);
			i++;
		}
    return (0);
}
