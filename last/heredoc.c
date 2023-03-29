#include "minishell.h"


static char *delimet(char *l)
{
    int i = 0;
    while(ft_strchr(" <",l[i]) != 0)
        i++;
    return(l +i);
}

int ft_search(char *word,char to_find)
{
    int i = 0;
    int len = 0;
    while(word[i])
    {
        if(word[i] == to_find)
            len++;   
        i++;
    }
    return(len);
}
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
    if(p)
        free(p);
    return(value);
}
void free2d(char **table)
{
    int i= 0;
    while(table[i])
        free(table[i++]);
}

char ***checkHerecode(char ***deriction,int len)
{
    int i = 0;
    int j  = 0;
   char ***heredocTable = ft_calloc(sizeof(char **) , len);
    while(deriction[i] != NULL)
    {
        j = 0;
        while(deriction[i][j])
        {
            if(ft_search(deriction[i][j],'<') == 2)
            {
                if(heredocTable[i] != NULL)
                    free2d(heredocTable[i]);
                heredocTable[i] = heredoc(delimet(deriction[i][j]));
            }
            j++;
        }
        i++;
    }
    return heredocTable;
}