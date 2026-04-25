#include "builtin.h"

int	pwd_builtin(void)
{
	char	buff[4096];

	if (getcwd(buff, sizeof(buff)) == NULL)
	{
		print_error("getcwd() error!\n");
		return (1);
	}
	printf("%s\n", buff);
	return (0);
}
