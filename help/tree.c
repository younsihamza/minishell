#include <stdio.h>
#include "minishell.h"



t_tree *create_node_tree(t_node *tokn)
{
    t_tree *new_node = malloc(sizeof(t_tree));
    new_node->tokn = tokn;
    new_node->left = NULL;
    new_node->right = NULL;
    return(new_node);
}

void add_back_left(t_tree **head, t_tree *new)
{
    t_tree *tmp;
    if(*head == NULL)
        *head = new;
    else 
    {
        tmp = *head;
        while(tmp->left != NULL)
        {
            tmp = tmp->left;
        }
        tmp->left= new;
    }
}

void add_back_right(t_tree **head, t_tree *new)
{
    t_tree *tmp;
    if(*head == NULL)
        *head = new;
    else 
    {
        tmp = *head;
        while(tmp->right != NULL)
        {
            tmp = tmp->right;
        }
        tmp->right= new;
    }
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
// void printf_tree(t_tree *root, int i)
// {
//     if(root == NULL || i  == 1)
//         return;
//     if((ft_strncmp(root->tokn->type ,"OP_OR",2) == 0 || ft_strncmp(root->tokn->type ,"OP_AND",2) == 0)&& i == 0)
//         if(root->right == NULL )
//         {
//             write(2,"ERROR parser\n",13);
//             i++;
//         }
//     if(ft_strncmp(root->tokn->type ,"OP_PIPE",1) == 0 || ft_strncmp(root->tokn->type ,"OP_ET",1) == 0)
//         if(root->right == NULL)
//             write(2,"ERROR parser\n",13);
//     if(ft_strncmp(root->tokn->data ,"<<",2) == 0 || ft_strncmp(root->tokn->data ,">>",1) == 0 || ft_strncmp(root->tokn->data ,">",1) == 0 || ft_strncmp(root->tokn->data ,"<",1) == 0 )
//         if(root->left == NULL)
//             write(2,"ERROR parser\n",13);
//     printf_tree(root->right,i);
//     printf_tree(root->left,i);
// }
int check_error_parser(t_tree **q,int len)
{
    int  i;

    i = 0;
    while(i < len)
    {
        if((ft_strncmp(q[i]->tokn->type ,"OP_OR",6) == 0 || ft_strncmp(q[i]->tokn->type ,"OP_AND",7) == 0)&& i == 0)
            if(q[i]->right == NULL )
                return(write(2,"ERROR parser\n",13));
    if(ft_strncmp(q[i]->tokn->type ,"OP_PIPE",8) == 0 || ft_strncmp(q[i]->tokn->type ,"OP_ET",6) == 0)
        if(q[i]->right == NULL || (ft_strncmp(q[i]->tokn->type ,"OP_PIPE",8) == 0 && q[i]->left == NULL))
            return(write(2,"ERROR parser\n",13));
    if(ft_strncmp(q[i]->tokn->data ,"<<",2) == 0 || ft_strncmp(q[i]->tokn->data ,">>",1) == 0 || ft_strncmp(q[i]->tokn->data ,">",1) == 0 || ft_strncmp(q[i]->tokn->data ,"<",1) == 0)
        if(q[i]->left == NULL)
            return(write(2,"ERROR parser\n",13));
    // printf("%s\n",q[i]->tokn->data);
        i++;
    }
    return(0);
}
t_tree *bulid_tree(t_node *head)
{
    t_node *ptr = head;
    t_tree *root = NULL;

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
        if(ft_strncmp(ptr->data ,"<<",2) == 0 || ft_strncmp(ptr->data ,">>",1) == 0 || ft_strncmp(ptr->data ,">",1) == 0 || ft_strncmp(ptr->data ,"<",1) == 0)
            root = insert(root,ptr);
        ptr = ptr->next;
    }
    ptr = head;
    while(ptr != NULL)
    {
        root = insert(root,ptr);
        ptr = ptr->next;
    }
    int len = len_list(head);
    if(len == 0)
        return(NULL);
    int rer = 0;
    int curent = 0;
    t_tree **queue;
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
    return(root);
}
