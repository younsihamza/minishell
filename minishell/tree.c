#include <stdio.h>
#include "minishell.h"



void printf_tree(t_tree *root,t_node **rot,int *i)
{
    if(root == NULL)
        return;
    printf_tree(root->right,rot,i);
//    printf("data == %s\n",root->tokn->data);
//    printf("type == %s\n",root->tokn->type);
//    printf("type == %d\n",root->tokn->space);
    rot[*i] = root->tokn;
    *i+= 1;
    printf_tree(root->left,rot,i);
}
t_tree *create_node_tree(t_node *tokn)
{
    t_tree *new_node = malloc(sizeof(t_tree));
    new_node->tokn = tokn;
    new_node->left = NULL;
    new_node->right = NULL;
    return(new_node);
}
// static char *delimet(char *l)
// {
//     int i = 0;
//     while(ft_strchr("$",l[i]) != 0)
//         i++;
//     return(l +i);
// }
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
t_node ** edit_rot(t_node **rot,int len)
{
    int i =0;
    int j = 0;
    char *hold = NULL;
    int cort= 0;
    t_node **list = ft_calloc(sizeof(t_node*),len + 1);

    while(rot[i] != NULL)
    {
        j = i + 1;
        if(ft_strncmp(rot[i]->type,"OP_PIPE",7) != 0 &&ft_strncmp(rot[i]->type,"OP_FILE",7) != 0)
        {
            while(rot[j] != NULL)
                {
                    if(ft_strncmp(rot[j]->type,"OP_PIPE",7) != 0 && rot[j]->space == 0 && ft_strncmp(rot[j]->type,"OP_FILE",7) != 0 )
                    {
                        rot[i]->data = ft_strjoin(rot[i]->data,rot[j]->data);
                    }else
                        break;
                        j++;
                }
        }
        list[cort++] = rot[i];
        i = j;
    }
    return (list);
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
        if(ft_strncmp(q[i]->tokn->type ,"OP_PIPE",8) == 0 )
            if(q[i]->right == NULL ||  q[i]->left == NULL)
                return(write(2,"ERROR parser\n",13));
        if(ft_strncmp(q[i]->tokn->type ,"OP_FILE",8) == 0)
        {
           if(q[i]->left == NULL)
                return(write(2,"ERROR parser\n",13));
        }
        i++;
    }
    return(0);
}
t_tree *bulid_tree(t_node *head,char **env)
{
    t_node *ptr = head;
    t_tree *root;
    t_tree **queue;
    int rer;
    int curent;


    root = NULL;
    ptr = head;
    while(ptr != NULL)
    {
        if(ft_strncmp(ptr->type ,"OP_PIPE",7) == 0 )
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
    free(queue);
    t_node **rot = ft_calloc(sizeof(t_node*) , len + 1);
    int a = 0;
    ft_inorder(root);
    printf_tree(root,rot ,&a);
    // // edit_rot(rot,len);
    // // expand(rot);
    transform_cmd(edit_rot(rot,len),env);
    // a = 0;
    free(rot);
    return(NULL);
}

