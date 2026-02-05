#include "builtin.h"

int pwd_builtin(void)
{
    char buff[4096];

    if(getcwd(buff, sizeof(buff)) != NULL)
    {
        printf("%s\n", buff);
        return (0);
    }
    else
    {
        printf("getcwd() error!\n");
    }
    return (1);
}