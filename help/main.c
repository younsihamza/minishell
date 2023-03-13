#include "minishell.h"


enum options {word,operater,greter_then,less_then,end,pip,flage};

int ft_strchre(char *s,int a )
{
    int i = 0 ;
    while(s[i])
    {
        if(s[i] ==(char)a)
            return(1);
        i++;
    }
    return(0);
}
t_node token(char *text)
{
    int i;
    i = 0;
    int j = 0;
    char *p = " |&><$\"";
    t_node *head;
    char *content;
    head = NULL;
    while(text[i])
    {
        if(text[i] == 34)
        {
            j = i;
            j++;
            while(text[j] != 34)
                j++;
            content  = ft_substr(text,i + 1,j - i - 1);
            add_back(&head,ft_lstnew(content,"DOUBLE"));
            content = NULL;
            i = j;
        }
          if(text[i] == 39)
        {
            j = i;
            j++;
            while(text[j] != 39)
                j++;
            content  = ft_substr(text,i + 1,j - i - 1);
            add_back(&head,ft_lstnew(content,"SINGLE"));
            content = NULL;
            i = j;
        }
        if(text[i] == '(')
        {
            j = i;
            while(text[j] != ')')
                j++;
            content  = ft_substr(text,i,j-i + 1);
            add_back(&head,ft_lstnew(content,"OP_SUB"));
            content = NULL;
            i = j;
        }
        if((text[i] >= 'a' && text[i] <='z'))
        {
            j = i;
            while(text[j] != ' ' && ft_strchre(p,text[j]) == 0 && text[j])
                j++;
            content  = ft_substr(text,i,j-i);
            add_back(&head,ft_lstnew(content,"OP_WR"));
            content = NULL;
            i = j;
        }
        if(text[i] >= '0' && text[i] <='9')
        {
            j = i;
            while(text[j] != ' ' && ft_strchre(p,text[j]) == 0  && text[j])
                j++;
            add_back(&head,ft_lstnew(ft_substr(text,i,j-i),"OP_NB"));
            i = j;
        }
        if(text[i] == '-')
        {
             j = i;
            while(text[j] != ' ' && ft_strchre(p,text[j]) == 0&& text[j])
                j++;
           content  = ft_substr(text,i,j-i + 1);
            add_back(&head,ft_lstnew(content,"OP"));
            content = NULL;
            i = j ;
        }
        if(text[i] == '<')
        {
            if(text[i+1] == '<')
            {
                content  = ft_substr(text,i,2);
                add_back(&head,ft_lstnew(content,"OP_H"));
                content = NULL;
                i++;
            }else
            {
               content  = ft_substr(text,i,1);
                add_back(&head,ft_lstnew(content,"OP_R"));
                content = NULL;
            } 
                while(text[i] == ' ')
                    i++;
                 j = i;
                while(text[j] != ' ' && ft_strchre(p,text[j]) == 0&& text[j])
                    j++;
                content  = ft_substr(text,i,j-i + 1);
                add_back(&head,ft_lstnew(content,"OP_FILE"));
                content = NULL;
                i = j ;
                
        }
        if(text[i] == '|')
        { 
            if(text[i+1] == '|')
            {
               content  = ft_substr(text,i,2);
                add_back(&head,ft_lstnew(content,"OP_OR"));
                content = NULL;
                i++;
            }else 
            {
               content  = ft_substr(text,i,1);
                add_back(&head,ft_lstnew(content,"OP_PIPE"));
                content = NULL;

            }
        }
        if(text[i] == '>')
        {
            if(text[i+1] == '>')
            {
                content  = ft_substr(text,i,2);
                add_back(&head,ft_lstnew(content,"OP_HD"));
                content = NULL;
                i++;
            }else
            {
                content  = ft_substr(text,i,1);
                add_back(&head,ft_lstnew(content,"OP_RD"));
                content = NULL;
            } 
        }
        if(text[i] == '$')
        {
            j = i;
            while(text[j] != ' ' && text[j] != '\t' && text[j])
                    j++;
            content  = ft_substr(text,i,j-i);
                add_back(&head,ft_lstnew(content,"OP_VR"));
                content = NULL;
            i = j;
        }
        if(text[i] == '&')
        {
            if(text[i+1] == '&')
            {
                content  = ft_substr(text,i,2);
                add_back(&head,ft_lstnew(content,"OP_AND"));
                content = NULL;
                i++;
            }else
            {
                
                content  = ft_substr(text,i,1);
                add_back(&head,ft_lstnew(content,"OP_ET"));
                content = NULL;
            } 
                
        }
        i++;
    }
    t_node *ptr;
    ptr = head;
    i = 1;
    while(ptr != NULL)
    {
        ptr->i = i;
        i++;
        ptr = ptr->next;
    }
    bulid_tree(head);
    // while(pp != NULL)
    // {
    //     printf("data = %s\n",pp->data);
    //     printf("data = %s\n",pp->type);
    //     pp = pp->next;
    // }
}

int main(int ac ,char **argv ,char **env)
    {
    char *p;
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