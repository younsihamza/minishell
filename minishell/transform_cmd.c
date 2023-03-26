#include "minishell.h"


static char *delimet(char *l)
{
    int i = 0;
    while(ft_strchr(" <",l[i]) != 0)
        i++;
    return(l +i);
}
// cat | skmad

t_node *simpleToken(char *text)
{
    int i = 0;
    t_node *list = NULL;
    int space = 0;
    int j = 0;

    while(text[i])
    {
        if(text[i] == '$')
        {
            j = i + 1;
            while(ft_strchr(" $",text[j]) == 0 && text[j])
                    j++;
            if(j != i +1)
                add_back(&list,ft_lstnew(ft_substr(text,i,j-i),"OP_VR",space));
            else
                add_back(&list,ft_lstnew(ft_substr(text,i,1),"OP_WR",space));
            i = j;
            space = 0;
        }
        if(ft_strchr("$",text[i]) == 0)
        {
            j = i;
            while(ft_strchr("$",text[j]) == 0 && text[j])
                j++;
            if(j != i)
            {
                add_back(&list,ft_lstnew(ft_substr(text,i,j-i),"OP_WR",space));
                i = j;
            }
            space = 0;
        }
    }
    return (list);
}

t_node  *ft_inorder(t_tree *root)
 {
    t_node *str = NULL;
    t_node *ptr = NULL;
    char *tmp = NULL;
    char *tokn = NULL;

    if(root == NULL)
        return NULL;
    ft_inorder(root->right);
    if(strcmp(root->tokn->type, "OP_VR") == 0)
    {
       root->tokn->data = getenv(&root->tokn->data[1]);
    }
    else if(strcmp(root->tokn->type, "DOUBLE") == 0)
    {
        str = simpleToken(root->tokn->data);

        ptr = str;
        while(str != NULL)
        {
           if(ft_strcmp(str->type, "OP_VR") == 0)
               str->data = getenv(&str->data[1]);
            str = str->next;
        }
        tokn = ft_calloc(sizeof(char) , 2);
        while(ptr != NULL)
        {
            tmp = tokn;
            tokn = ft_strjoin(tokn, ptr->data);
            free(tmp);
            ptr = ptr->next;
        }
       root->tokn->data = tokn;
     }
    ft_inorder(root->left);
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
                // printf("|==%s\n",delimet(deriction[i][j]));
            if(ft_search(deriction[i][j],'<') == 2)
            {
                heredocTable[i] = heredoc(delimet(deriction[i][j]));
            }
            j++;
        }
        i++;
    }
    return heredocTable;
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
    j = 0;
    while(rot[i])
    {
        while(rot[i])
        {
            if(ft_strcmp("OP_PIPE",rot[i]->type) != 0)
            {
                if(ft_strcmp(rot[i]->type,"OP_FILE") != 0)
                    command = ft_join2d(command , rot[i]->data);
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
            file = ft_join2d(file,ft_strjoin(rot[i]->data,rot[i + 1]->data));
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
    execute(&d,env);
}
