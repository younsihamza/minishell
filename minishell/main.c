#include "minishell.h"


t_node *token(char *text)
{
    int i;
    int j;
    char *p = " |&><$\"";
    t_tree *root;
    t_node *head;
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
            add_back(&head,ft_lstnew(ft_substr(text,i + 1,j - i - 1),"DOUBLE"));
            i = j + 1;
        }
        if(text[i] == 39)
        {
            j = i + 1;
            while(text[j] != 39 && text[j])
                j++;
            add_back(&head,ft_lstnew(ft_substr(text,i + 1,j - i - 1),"SINGLE"));
            i = j + 1;
        }
        if(text[i] == '(')
        {
            j = i;
            while(text[j] != ')')
                j++;
            add_back(&head,ft_lstnew(ft_substr(text,i,j-i + 1),"OP_SUB"));
            i = j;
        }
        if(text[i] == '-')
        {
             j = i;
            while(text[j] != ' ' && ft_strchr(p,text[j]) == 0&& text[j])
                j++;
            add_back(&head,ft_lstnew(ft_substr(text,i,j-i),"OP"));
            i = j ;
        }
        if(text[i] == '<')
        {
            j  = i;
            if(text[j+1] == '<')
                j+=2;
            else
                j++;
                while(text[j] == ' ')
                    j++;
                while(text[j] != ' ' && ft_strchr(p,text[j]) == 0 && text[j])
                    j++;
                if(j != i)
                {
                    add_back(&head,ft_lstnew(ft_substr(text,i,j-i),"OP_FILE"));
                    i = j;
                }
        }
        if(text[i] == '|')
        { 
            if(text[i+1] == '|')
            {
                add_back(&head,ft_lstnew(ft_substr(text,i,2),"OP_OR"));
                i += 2;
            }else 
            {
                add_back(&head,ft_lstnew(ft_substr(text,i,1),"OP_PIPE"));
                i++;
            }
        }
        if(text[i] == '>')
        {
            j = i;
            if(text[i+1] == '>')
            {
                j += 2;
            }else
                j++;
                while(text[j] == ' ')
                    j++;
                while(text[j] != ' ' && ft_strchr(p,text[j]) == 0 && text[j])
                    j++;
                if(j != i)
                {
                    add_back(&head,ft_lstnew(ft_substr(text,i,j-i),"OP_FILE"));
                    i = j ;
                }
        }
        if(text[i] == '$')
        {
            j = i;
            while(text[j] != ' ' && text[j] != '\t' && text[j])
                    j++;
                add_back(&head,ft_lstnew(ft_substr(text,i,j-i),"OP_VR"));
            i = j;
        }
        if(text[i] == '&')
        {
            if(text[i+1] == '&')
            {
                add_back(&head,ft_lstnew(ft_substr(text,i,2),"OP_AND"));
                i += 2;
            }else
            {
                add_back(&head,ft_lstnew(ft_substr(text,i,1),"OP_ET"));
                i++;
            }  
        }
        if(ft_strchr(p,text[i]) == 0)
        {
            j = i;
            while(text[i] != ' ' && ft_strchr(p,text[j]) == 0 && text[j])
                j++;
            if(j != i)
            {
                add_back(&head,ft_lstnew(ft_substr(text,i,j-i),"OP_WR"));
                i = j;
            }
        }
        while(text[i] == ' ' && text[i])
            i++;
    }
    ptr = head;
    i = 1;
    while(ptr != NULL)
    {
        ptr->i = i;
        i++;
        ptr = ptr->next;
    }
    root = bulid_tree(head);
    return(NULL);
}

int main(int ac ,char **argv ,char **env)
    {
    char *text;
    char path[100];
    if(ac != 1)
        return (1);
    while( (text = readline("$> ")) != NULL)
    {
        add_history(text);
        token(text);
    }
 }