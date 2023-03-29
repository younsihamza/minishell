#include "minishell.h"

int ft_strcmp(char *str1 , char *str2)
{
	int i = 0;
	while(str1[i] && str2[i] && str1[i] == str2[i])
		i++;
	return(str1[i] - str2[i]);
}
void	*ft_calloc(size_t nitems, size_t size)
{
	size_t	i;
	void	*p;

	i = 0;
	p = malloc(size * nitems);
	if (!p)
		return (NULL);
	while (i < nitems * size)
	{
		*(char *)(p + i) = '\0';
		i++;
	}
	return (p);
}

size_t	ft_strlen(const char *str)
{
	unsigned int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

static char	*strimplement(char *str, char const *s1, char const *s2)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	while (*(s1 + j))
	{
		*(str + i) = *(s1 + j);
		j++;
		i++;
	}
	j = 0;
	while (*(s2 + j))
	{
		*(str + i) = *(s2 + j);
		j++;
		i++;
	}
	*(str + i) = '\0';
	return (str);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char			*str;

	str = NULL;
	if (!s1 || !s2)
		return (str);
	str = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (NULL);
	strimplement(str, s1, s2);
	return (str);
}

char	*ft_substr(char const *s, size_t start, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	r;
	char	*p;

	j = 0 ;
	i = start ;
	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
	{
		p = ft_calloc(sizeof(char), 1);
		return (p);
	}
	if (ft_strlen(s + start) > len)
		r = len;
	else
		r = ft_strlen(s + start);
	p = ft_calloc(sizeof(char), r + 1);
	if (!p)
		return (NULL);
	while (j < r)
		*(p + j++) = *(s + i++);
	return (p);
}

int	ft_strncmp( const char *str1, const char *str2, size_t n)
{
	size_t			i;
	unsigned char	*str11 ;
	unsigned char	*str22 ;

	str11 = (unsigned char *)str1 ;
	str22 = (unsigned char *)str2 ;
	i = 0;
	if (n == 0)
		return (0);
	while ((*(str11 + i) || *(str22 + i))
		&& *(str11 + i) == *(str22 + i) && i < n - 1)
		i++;
	return (*(str11 + i) - *(str22 + i));
}

int ft_strchr(char *str ,char a)
{
    int i ;
    i = 0;
    while(str[i])
    {
        if( str[i] == a)
            return(1);
        i++;
    }
    return(0);
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

int ft_strlen2d(char **s1)
{
    int i;
    i = 0;
    while(s1[i])
        i++;
    return(i);
}

char **ft_join2d(char **env ,char *var)
{
    char **p;
    if(var == NULL)
        return(env);
    if(env == NULL)
        {
            p = ft_calloc(sizeof(char *),2);
            p[0] = var;
            return(p);
        }
    p = ft_calloc(sizeof(char *),ft_strlen2d(env) + 2);
    int i = 0;
    while(env[i])
    {
        p[i] = env[i];
        i++;
    }
    p[i] = var;
    return(p);
}
char *get_env_arr(char *find, t_vars *env)
{
    t_vars *ptr =NULL;

    ptr = env;
    while(ptr != NULL) 
    {
        if(ft_strncmp(ptr->data, find, ft_strlen(find)) == 0)
            return ptr->data + ft_strlen(find) +1;
        ptr = ptr->next;
    }
    return NULL; 
}