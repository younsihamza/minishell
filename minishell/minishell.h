#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
 #include <fcntl.h>
  #include <signal.h>
 #include <string.h>
  #include <sys/stat.h>

typedef struct node 
{
    char *data;
    int i;
    int space;
    char *type;
    struct node *next;
}t_node;
typedef struct tree_node
{
    t_node *tokn;
    struct tree_node *left;
    struct tree_node *right;
}t_tree;

typedef struct data{
     t_node **op;
     char ***cmd;
     char ***deriction;
     char ***heredoc;
}t_data;

t_node	*ft_lstnew(void *content, char *type, int space);
void	add_back(t_node **lst, t_node *new);
t_node	*ft_lstlast(t_node *lst);
char	*ft_strnstr(const char *big, const char *little, size_t len);
void	*ft_calloc(size_t nitems, size_t size);
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
t_node *token(char *text,char **env);
size_t	ft_strlen(const char *str);
char	*ft_substr(char const *s, size_t start, size_t len);
char	*ft_strtrim(char const *s1, char const *set);
int	ft_strncmp( const char *str1, const char *str2, size_t n);
void    ft_inorder(t_tree *root);
void ft_putstr(char *str,int fd);
t_tree *bulid_tree(t_node *head,char **env);
int	ft_memcmp(const void *str1, const void *str2, size_t n);
int ft_chr_index(char *str ,char a,int *len);
int ft_strchr(char *str ,char a);
char **ft_join2d(char **env ,char *var);
int ft_strlen2d(char **s1);
int ft_strcmp(char *str1 , char *str2);
void transform_cmd(t_node **rot,char **env);
void cd (char *p);
int ft_search(char *word,char to_find);
char **heredoc(char *stop);
void echo(char **cmd);
// char **heredoc(char *stop);
void execute(t_data *var,char **env);
#endif // !MINISHELL_H
