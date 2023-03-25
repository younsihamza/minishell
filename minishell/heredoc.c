#include "minishell.h"

char **heredoc(char *stop)
{
    char **value = NULL;
    char **tmp = NULL;
    char *p;
    while(1)
    {
        p = readline("herecod>");
        if(ft_strcmp(stop,p) == 0)
            break;
        else{
            tmp = value;
            value = ft_join2d(value,p);
            free(tmp);
        }
    }
    return(value);
}
// int main()
// {
//     char **p =heredoc("hamza");
//     int fd = open("hg",O_RDWR,0644);
//     int i = 0;
//     if(p == NULL)
//         return(0);
//     while(p[i])
//         printf("%s\n",p[i++]);
// }