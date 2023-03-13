#include "header.h"

t_root *create_node(t_node *data)
{
    t_root *new_node = malloc(sizeof(t_root));
    new_node->data = data;
    new_node->left = NULL;
    new_node->right = NULL;
    return(new_node);
}

t_root *insert(t_root *root ,t_node *ptr)
{
    if(root == NULL)
        root = create_node(ptr);
    else if(root->data->number  < ptr->number)
        root->left =  insert(root->left,ptr);
    else if(root->data->number > ptr->number)
        root->right = insert(root->right,ptr);
    return(root);
}

t_root *create_tree(t_node *head)
{
    t_node *ptr = head;
    t_root *root = NULL;
    t_root *ptr1 = root;
    while(ptr != NULL)
    {
        if(strncmp(ptr->data, "||", 2) == 0 || strncmp(ptr->data, "&&", 2) == 0)
        {
           root = insert(root, ptr);
        }
        ptr = ptr->next;
    }
    ptr = head;
    while(ptr != NULL)
    {
    {
        if(strncmp(ptr->data, "|", 1) == 0)
           root =  insert(root, ptr);
        ptr = ptr->next;
    }
    }
     ptr = head;
    while(ptr != NULL)
    {
        if(strncmp(ptr->data ,"<<", 2) == 0 || strncmp(ptr->data ,">>", 2) == 0 || strncmp(ptr->data ,">", 1) == 0 || strncmp(ptr->data ,"<", 1) == 0)
           root =  insert(root, ptr);
        ptr = ptr->next;
    }
    return root;
}


