#include "minishell.h"

t_node *token(char *text)
{
    int i;
    int j;
    char *p = " |><$\"";
    t_node *head;
    int space = 0;
    t_node *ptr;
    head = NULL;
    i = 0;
    j = 0;
    while(text[i])
    {
        if(text[i] == 34)
        {
            j = i + 1;
            while(text[j] != 34 && text[j])
                j++;
            add_back(&head,ft_lstnew(ft_substr(text,i + 1,j - i - 1),"DOUBLE",space));
            i = j + 1;
            space = 0;
        }
        if(text[i] == 39)
        {
            j = i + 1;
            while(text[j] != 39 && text[j])
                j++;
            add_back(&head,ft_lstnew(ft_substr(text,i + 1,j - i - 1),"SINGLE",space));
            i = j + 1;
            space = 0;
        }
        if(text[i] == '<')
        {
            j  = i;
            if(text[j+1] == '<')
                j+=2;
            else
                j++;
                if(j != i)
                {
                    add_back(&head,ft_lstnew(ft_substr(text,i,j-i),"OP_FILE",space));
                    i = j;
                }
                 space = 0;
        }
        if(text[i] == '|')
        { 

                add_back(&head,ft_lstnew(ft_substr(text,i,1),"OP_PIPE",space));
                i++;
                space = 0;
        }
        if(text[i] == '>')
        {
            j = i;
            if(text[i+1] == '>')
            {
                j += 2;
            }else
                j++;
                if(j != i)
                {
                    add_back(&head,ft_lstnew(ft_substr(text,i,j-i),"OP_FILE",space));
                    i = j ;
                }
                space = 0;
        }
        if(text[i] == '$')
        {
            j = i + 1;
            while(ft_strchr(" |><$\"",text[j]) == 0 && text[j])
                    j++;
            if(j != i +1)
                add_back(&head,ft_lstnew(ft_substr(text,i,j-i),"OP_VR",space));
            else
                add_back(&head,ft_lstnew(ft_substr(text,i,1),"OP_WR",space));
            i = j;
            space = 0;
        }
        if(ft_strchr(p,text[i]) == 0)
        {
            j = i;
            while(text[i] != ' ' && ft_strchr(p,text[j]) == 0 && text[j])
                j++;
            if(j != i)
            {
                add_back(&head,ft_lstnew(ft_substr(text,i,j-i),"OP_WR",space));
                i = j;
            }
            space = 0;
        }

            while(text[i] == ' ' && text[i])
            {
                space = 1;
                i++;
            }
    }
    ptr = head;
    i = 1;
    while(ptr != NULL)
    {
        ptr->i = i;
        i++;
        ptr = ptr->next;
    }
    free(text);
    return(head);
}