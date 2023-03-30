#include "minishell.h"

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

void  ft_inorder(t_tree *root,t_vars *env)
 {
    t_node *str = NULL;
    t_node *ptr = NULL;
    char *tmp = NULL;
    char *tokn = NULL;

    if(root == NULL)
        return ;
    ft_inorder(root->right,env);
    if(strcmp(root->tokn->type, "OP_VR") == 0)
    {
       tmp = get_env_arr(&root->tokn->data[1],env);
        free(root->tokn->data);
        if(tmp != NULL)
        {
            root->tokn->data = ft_strdup(tmp);
        }
        else 
            root->tokn->data =ft_calloc(sizeof(char) , 2);
    }
    else if(strcmp(root->tokn->type, "DOUBLE") == 0)
    {
        str = simpleToken(root->tokn->data);

        ptr = str;
        while(str != NULL)
        {
           if(ft_strcmp(str->type, "OP_VR") == 0)
           {
               tmp = get_env_arr(&str->data[1],env);
               free(str->data);
               if(tmp != NULL)
                    str->data =ft_strdup(tmp);
                else 
                   str->data =ft_calloc(sizeof(char) , 2);
           }
            str = str->next;
        }
        tokn = ft_calloc(sizeof(char) , 2);

        int i = 0;
        while(ptr != NULL)
        {
            if(ptr->data != NULL)
            {
                tmp = tokn;
                tokn = ft_strjoin(tokn, ptr->data);
                free(tmp);
                free(ptr->data);
            }
            str = ptr;
            ptr = ptr->next;
            free(str);
        }
        free(root->tokn->data);
       root->tokn->data = tokn;
     }
    ft_inorder(root->left,env);
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
                        hold = rot[i]->data;
                        rot[i]->data = ft_strjoin(rot[i]->data,rot[j]->data);
                        free(hold);
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
void makeStack(t_tree *root,t_node **rot,int *i)
{
    if(root == NULL)
        return;
    makeStack(root->right,rot,i);
//    printf("type == %s\n",root->tokn->type);
//    printf("type == %d\n",root->tokn->space);
    rot[*i] = root->tokn;
    *i+= 1;
    makeStack(root->left,rot,i);
//    printf("data == %s\n",root->tokn->data);
}
void free_tree(t_tree *root)
{
    if(root == NULL)
        return;
    free_tree(root->right);
    free_tree(root->left);
    free(root);
}
t_tree *bulid_tree(t_node *head, t_vars *env,  t_vars *declare)
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
    
    if(check_error_parser(queue,len) != 0)
    {
        free(queue);
        free_tree(root);
        while(head != NULL)
    {
        ptr = head;
        free(ptr->data);
        head = head->next;
        free(ptr);
    }
        return(NULL);
    }
    free(queue);
    int a = 0;
    t_node **rot = ft_calloc(sizeof(t_node*) , len + 1);
    t_node **list;
    ft_inorder(root,env);
    makeStack(root,rot ,&a);
    list = edit_rot(rot,len);
    transform_cmd(list,env,declare);
    free_tree(root);
    free(list);
    while(head != NULL)
    {
        ptr = head;
        free(ptr->data);
        head = head->next;
        free(ptr);
    }
    free(rot);
    return(NULL);
}