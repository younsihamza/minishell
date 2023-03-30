#include "minishell.h"

void ft_tolower(char ***cmd)
{
    int i= 0;
    int j = 0;
    while(cmd[i])
    {
        j = 0;
        while(cmd[i][0][j])
        {
            if(cmd[i][0][j] >='A' && cmd[i][0][j] <= 'Z')
                cmd[i][0][j] += 32;
            j++; 
        }
        i++;
    }
}

void transform_cmd(t_node **rot,t_vars *env,  t_vars *declare)
{
    int i;
    int len;
    int j;
    char **splitVar =NULL;
    t_data d;
    char ***heredocTable;
    j = 0;
    len = 0;
    i = 0;
    while(rot[i])
    {
        if(ft_strcmp("OP_PIPE",rot[i]->type) == 0)
            len++;
        i++;
    }
    d.op = ft_calloc(sizeof(t_node *),len +2);
    i = 0;
    while(rot[i])
    {
        if(ft_strcmp("OP_PIPE",rot[i]->type) == 0)
        {
            d.op[j] = rot[i];
            j++;
        }
        i++;
    }
    i = 0;
    d.cmd = ft_calloc(sizeof(char **),len + 2);
    char **command = NULL;
    char **tmp2d;
    char **tmpVar;
    int r = 0;
    char *tmp;
    j = 0;
    while(rot[i])
    {
        while(rot[i])
        {
            if(ft_strcmp("OP_PIPE",rot[i]->type) != 0)
            {
                if(ft_strcmp(rot[i]->type,"OP_FILE") != 0)
                {
                    if(ft_strcmp(rot[i]->type,"OP_VR") == 0)
                    {
                        splitVar = ft_split(rot[i]->data,' ');
                            
                        if(splitVar != NULL)
                        {
                            while(splitVar[r])
                                {
                                    tmp2d=command;
                                    command = ft_join2d(command , splitVar[r]);
                                    free(tmp2d);
                                    r++;
                                }
                                free(splitVar);
                        }
                    }else
                    {
                        tmp2d=command;
                        command = ft_join2d(command ,ft_strdup(rot[i]->data));
                        free(tmp2d);
                    }
                }
                else
                    i++;
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
        if(ft_strcmp(rot[i]->type,"OP_FILE") == 0)
        {
            tmp2d = file;
            file = ft_join2d(file,ft_strjoin(rot[i]->data,rot[i + 1]->data));
            free(tmp2d);
            i++;
        }
        if((ft_strcmp("OP_PIPE",rot[i]->type) == 0 || rot[i +1] == NULL ) && file != NULL )
        {
            d.deriction[j] = file;
            file = NULL;
            j++; 
        }
        i++;
    }
    d.heredoc = checkHerecode(d.deriction,len + 2);
    ft_tolower(d.cmd);
    execute(&d,env,declare);
    i = 0;
    while(i <= len )
    {
        if(d.heredoc[i])
        {
            free2d(d.heredoc[i]);
            free(d.heredoc[i]);
        }
        i++;
    }
    free(d.heredoc);
    free(d.op);
    i = 0;
    while(d.cmd[i])
    {
            free2d(d.cmd[i]);
            free(d.cmd[i]);
        i++;
    }
    free(d.cmd);
   i = 0;
    while(i <= len)
    {
        if(d.deriction[i] != NULL)
        {
            free2d(d.deriction[i]);
            free(d.deriction[i]);
        }
        i++;
    }
    free(d.deriction);
}