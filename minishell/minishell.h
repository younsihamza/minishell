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

typedef struct vars
{
    char *data;
    struct vars *next;
    
}  t_vars;

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

char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
t_node	*ft_lstlast(t_node *lst);
void	add_back(t_node **lst, t_node *new);
t_node	*ft_lstnew(void *content, char *type, int space);
char	*ft_substr(char const *s, size_t start, size_t len);
int	ft_strncmp( const char *str1, const char *str2, size_t n);
t_tree *bulid_tree(t_node *head, t_vars *env,  t_vars *declare);
int ft_strchr(char *str ,char a);
t_tree *create_node_tree(t_node *tokn);
t_tree *insert(t_tree *root ,t_node *ptr);
int len_list(t_node *head);
void	*ft_calloc(size_t nitems, size_t size);
int check_error_parser(t_tree **q,int len);
t_node *token(char *text);
char **ft_join2d(char **env ,char *var);
int ft_strcmp(char *str1 , char *str2);
int ft_strlen2d(char **s1);
void transform_cmd(t_node **rot,t_vars *env,  t_vars *declare);
int ft_search(char *word,char to_find);
char ***checkHerecode(char ***deriction,int len);
char *get_env_arr(char *find, t_vars *env);
void execute(t_data *var,t_vars *env,  t_vars *declare);
void ft_putstr(char *str,int fd);
void	add_envback(t_vars **lst, t_vars *new);
t_vars	*ft_lstlastenv(t_vars *lst);
t_vars	*ft_envnew(void *content);
size_t	ft_strlen(const char *str);
char	*ft_strdup(const char *s);
void free2d(char **table);
#endif // !