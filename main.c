#include "header.h"



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
t_node scanner(char *text, t_node **head)
{
    int i;
    i = 0;
    int k = 0;
    int j = 0;
    char *p = " |&><$\"";
    char *content;
    while(text[i])
    {
        if(text[i] == 34)
        {
            j = i;
            j++;
            //if(text[j] == '\0')
                // create quote for the charchers
            while(text[j] != 34)
                j++;
            k++;
            content  = ft_substr(text,i + 1,j - i - 1);
            add_back(head,ft_lstnew(content,"DOUBLE", k));
            content = NULL;
            i = j;
        }
        if(text[i] == 39)
        {
            j = i;
            j++;
            //if(text[j] == '\0')
                // create quote for the charchers
            while(text[j] != 39)
                j++;
            k++;
            content  = ft_substr(text,i + 1,j - i - 1);
            add_back(head,ft_lstnew(content,"SINGLE", k));
            content = NULL;
            i = j;
        }
        if(text[i] == '(')
        {
            j = i;
            while(text[j] != ')')
                j++;
            k++;
            content  = ft_substr(text,i + 1,j - i);
            add_back(head,ft_lstnew(content,"OP_SUB", k));
            content = NULL;
            i = j;
        }
        if(((text[i] >= 'a' && text[i] <='z') || (text[i] >= 'A' && text[i] <='Z')))
        {
            j = i;
            while(text[j] != ' ' && ft_strchre(p,text[j]) == 0 && text[j])
                j++;
            k++;
            content  = ft_substr(text,i,j-i + 1);
            add_back(head,ft_lstnew(content,"OP_WR", k));
            content = NULL;
            i = j;
        }
        if(text[i] >= '0' && text[i] <='9')
        {
            j = i;
            while(text[j] != ' ' && ft_strchre(p,text[j]) == 0  && text[j])
                j++;
            k++;
            add_back(head,ft_lstnew(ft_substr(text,i,j-i),"OP_NB", k));
            i = j;
        }
        if(text[i] == '-')
        {
             j = i;
            while(text[j] != ' ' && ft_strchre(p,text[j]) == 0&& text[j])
                j++;
            k++;
           content  = ft_substr(text,i,j-i + 1);
            add_back(head,ft_lstnew(content,"OP", k));
            content = NULL;
            i = j ;
        }
        if(text[i] == '<')
        {
            if(text[i+1] == '<')
            {
                k++;
                content  = ft_substr(text,i,2);
                add_back(head,ft_lstnew(content,"OP_H", k));
                content = NULL;
                i++;
            }else
            {
                k++;
               content  = ft_substr(text,i,1);
                add_back(head,ft_lstnew(content,"OP_R", k));
                content = NULL;
            } 
        }
        if(text[i] == '|')
        { 
            if(text[i+1] == '|')
            {
                k++;
               content  = ft_substr(text,i,2);
                add_back(head,ft_lstnew(content,"OP_OR",k));
                content = NULL;
                i++;
            }else 
            {
                k++;
               content  = ft_substr(text,i,1);
                add_back(head,ft_lstnew(content,"OP_PIPE", k));
                content = NULL;

            }
        }
        if(text[i] == '>')
        {
            if(text[i+1] == '>')
            {
                k++;
                content  = ft_substr(text,i,2);
                add_back(head,ft_lstnew(content,"OP_HD", k));
                content = NULL;
                i++;
            }else
            {
                k++;
                content  = ft_substr(text,i,1);
                add_back(head,ft_lstnew(content,"OP_RD", k));
                content = NULL;
            } 
        }
        if(text[i] == '$')
        {
            j = i;
            while(text[j] != ' ' && text[j] != '\t' && text[j])
                    j++;
            k++;
            content  = ft_substr(text,i,j-i + 1);
                add_back(head,ft_lstnew(content,"OP_VR", k));
                content = NULL;
            i = j;
        }
        if(text[i] == '&')
        {
            if(text[i+1] == '&')
            {
                k++;
                content  = ft_substr(text,i,2);
                add_back(head,ft_lstnew(content,"OP_AND", k));
                content = NULL;
                i++;
            }else
            {
                k++;
                content  = ft_substr(text,i,1);
                add_back(head,ft_lstnew(content,"OP_ET", k));
                content = NULL;
            } 
                
        }
        i++;
    }
}
void  handleSignal (int sig)
{
    printf("signal: %d\n", sig);
}

int main()
{

    
    char buffer[81];
    char **token;
    char *cmd = NULL;
    char *usename = NULL;
    t_node *head = NULL;

    usename =  getenv("USER");
    printf("username: %s\n", usename);


    while (1)
    {
                cmd = readline(">>>");

        if(strcmp(cmd, "\0") == 0 || strcmp(cmd, "\n") == 0)
        {
            continue;
        }
        if(strcmp(cmd, "exit") == 0)
        {
            exit(0);
        }
         scanner(cmd , &head);
        t_root *root = create_tree(head);
        // if(root == NULL)
        //     printf("Failed to create");
        while(root != NULL) 
         {

            printf("%s\n", root->data->data);
            printf("%d\n", root->data->number);
            root = root->left;

         }
    }

    return 0;

}