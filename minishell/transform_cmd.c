#include "minishell.h"


static char *delimet(char *l)
{
    int i = 0;
    while(ft_strchr(" <",l[i]) != 0)
        i++;
    return(l +i);
}
// cat | skmad
void checkHerecode(char ***deriction)
{
    int i = 0;
    int j ;
    while(deriction[i])
    {
        j = 0;
        while(deriction[i][j])
        {
            if(ft_search(deriction[i][j],'<') == 2)
                heredoc(delimet(deriction[i][j]));
            j++;
        }
        i++;
    }
}

void transform_cmd(t_node **rot,char **env)
{
    int i;
    int len;
    int j;
    t_data d;
    char ***heredocTable;
    j = 0;
    len = 0;
    i = 0;
    while(rot[i])
    {
        if(ft_strchr("|&",rot[i]->data[0]) != 0)
            len++;
        i++;
    }
    d.op = ft_calloc(sizeof(t_node *),len +2);
    i = 0;
    while(rot[i])
    {
        if(ft_strchr("|&",rot[i]->data[0]) != 0)
        {
            d.op[j] = rot[i];
            j++;
        }
        i++;
    }
    i = 0;
    d.cmd = ft_calloc(sizeof(char **),len + 2);
    char **command = NULL;
    j = 0;
    while(rot[i])
    {
        while(rot[i])
        {
            if(ft_strchr("|&",rot[i]->data[0]) == 0)
            {
                if(ft_strchr("<>",rot[i]->data[0]) == 0)
                    command = ft_join2d(command , rot[i]->data);
            }
            else 
                break;
            i++;
        }
        if(command != NULL)
        {
            d.cmd[j] =  command;
            command = NULL;
            j++;
        }
        if(rot[i] != NULL)
            i++;
    }
    d.deriction = ft_calloc(sizeof(char **),len + 2);
    i = 0;
    j = 0;
    char **file = NULL;
    while(rot[i])
    {
        if(ft_strchr("<>",rot[i]->data[0]) != 0 && ft_strchr("|&",rot[i]->data[0]) == 0 && ft_strcmp(rot[i]->type,"OP_FILE") == 0)
        {
            file = ft_join2d(file,rot[i]->data);
        }
        if((ft_strchr("|&",rot[i]->data[0]) != 0 || rot[i +1] == NULL ) && file != NULL )
        {
            d.deriction[j] = file;
            file = NULL;
            j++; 
        }
        i++;
    }
    checkHerecode(d.deriction);
    execute(&d,env);
}
