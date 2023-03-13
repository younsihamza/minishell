       #include <stdio.h>
       #include <readline/readline.h>
       #include <readline/history.h>
       #include <unistd.h>
       #include <stdlib.h>
       #include <signal.h>
       #include <unistd.h>
       #include <string.h>





typedef struct node 
{
    char *data;
    char *type;
    int   number;
    struct node *next;
    
} t_node;

typedef struct tree
    {
        t_node *data;
       struct  tree  *left;
       struct  tree *right;
    } t_root;

char	*ft_strtrim(char const *s1, char const *set);
void	*ft_calloc(size_t nitems, size_t size);
char	*ft_substr(char const *s, unsigned int start, size_t len);
t_node	*ft_lstnew(void *content, char *type, int number);
void	add_back(t_node **lst, t_node *new);
t_root     *create_tree(t_node *head);
size_t	ft_strlen(const char *str);
char *ft_type(char *str);
char	*ft_strjoin(char const *s1, char const *s2);
