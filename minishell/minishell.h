#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <unistd.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>

typedef struct node 
{
    char *data;
    int i;
    char *type;
    struct node *next;
}t_node;
typedef struct tree_node
{
    t_node *tokn;
    struct tree_node *left;
    struct tree_node *right;
}t_tree;
t_node	*ft_lstnew(void *content, char *type);
void	add_back(t_node **lst, t_node *new);
t_node	*ft_lstlast(t_node *lst);
void	*ft_calloc(size_t nitems, size_t size);
char	**ft_split(char const *s, char c);
t_node *token(char *text);
size_t	ft_strlen(const char *str);
char	*ft_substr(char const *s, size_t start, size_t len);
char	*ft_strtrim(char const *s1, char const *set);
int	ft_strncmp( const char *str1, const char *str2, size_t n);
t_tree *bulid_tree(t_node *head);
int	ft_memcmp(const void *str1, const void *str2, size_t n);
int ft_strchr(char *str ,char a);
#endif // !MINISHELL_H
