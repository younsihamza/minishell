#include <stdio.h>
#include "minishell.h"



void printf_tree(t_tree *root)
{
    if(root == NULL)
        return;
    printf("data == %s\n",root->tokn->data);
    printf_tree(root->right);
    printf_tree(root->left);
}
t_tree *create_node_tree(t_node *tokn)
{
    t_tree *new_node = malloc(sizeof(t_tree));
    new_node->tokn = tokn;
    new_node->left = NULL;
    new_node->right = NULL;
    return(new_node);
}

t_tree *insert(t_tree *root ,t_node *ptr)
{
    if(root == NULL)
        root = create_node_tree(ptr);
    else if(root->tokn->i < ptr->i)
        root->left =  insert(root->left,ptr);
    else if(root->tokn->i > ptr->i)
        root->right =  insert(root->right,ptr);
    return(root);
}
int len_list(t_node *head)
{
    int i; 
    i = 0;
    while(head != NULL)
    {
        i++;
        head = head->next;
    }
    return(i);
}
int check_error_parser(t_tree **q,int len)
{
    int  i;
    int j ;
    int k;
    char *p = " |&><$\"";

    i = 0;
    while(i < len)
    {
        if((ft_strncmp(q[i]->tokn->type ,"OP_OR",6) == 0 || ft_strncmp(q[i]->tokn->type ,"OP_AND",7) == 0)&& i == 0)
            if(q[i]->right == NULL )
                return(write(2,"ERROR parser\n",13));
        if(ft_strncmp(q[i]->tokn->type ,"OP_PIPE",8) == 0 || ft_strncmp(q[i]->tokn->type ,"OP_ET",6) == 0)
            if(q[i]->right == NULL || (ft_strncmp(q[i]->tokn->type ,"OP_PIPE",8) == 0 && q[i]->left == NULL))
                return(write(2,"ERROR parser\n",13));
        if(ft_strncmp(q[i]->tokn->type ,"OP_FILE",8) == 0)
        {
            j = 0;
            k = 0;
            while(q[i]->tokn->data[j])
            {
                if(q[i]->tokn->data[j]> 32  && q[i]->tokn->data[j] < 127 && ft_strchr("<>",q[i]->tokn->data[j]) != 1)
                    k++;
                j++;
            }
            if(k == 0)
                return(write(2,"ERROR parser\n",13));
        }
        i++;
    }
    return(0);
}
t_tree *bulid_tree(t_node *head)
{
    t_node *ptr = head;
    t_tree *root;
    t_tree **queue;
    int rer;
    int curent;

    root = NULL;
    while(ptr != NULL)
    {
        if(ft_strncmp(ptr->data ,"||",2) == 0 || ft_strncmp(ptr->data ,"&&",2) == 0)
                root = insert(root,ptr);
        ptr = ptr->next;
    }
    ptr = head;
    while(ptr != NULL)
    {
        if(ft_strncmp(ptr->data ,"|",1) == 0 || ft_strncmp(ptr->data ,"&",1) == 0)
            root = insert(root,ptr);
        ptr = ptr->next;
    }
    ptr = head;
    while(ptr != NULL)
    {
        if(ft_strncmp(ptr->type ,"OP_FILE",8) == 0)
            root = insert(root,ptr);
        ptr = ptr->next;
    }
    ptr = head;
    while(ptr != NULL)
    {
        root = insert(root,ptr);
        ptr = ptr->next;
    }
    int len;
    len = len_list(head);
    if(len == 0)
        return(NULL);
    rer = 0;
    curent = 0;
    queue = malloc(sizeof(t_tree*)*len);
    queue[rer] = root;
    rer++;
    while(curent != rer)
    {
        if(queue[curent]->right != NULL)
            queue[rer++] = queue[curent]->right;
        if(queue[curent]->left != NULL)
            queue[rer++] = queue[curent]->left;
        curent++;
    }
    check_error_parser(queue,len);
    printf_tree(root);
    return(NULL);
}
