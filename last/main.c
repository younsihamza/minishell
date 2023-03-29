#include "minishell.h"

t_vars	*ft_envnew(void *content)
{
	t_vars	*p;

	p = malloc(sizeof(t_vars));
	if (!p)
		return (NULL);
	p->data = (char *)content;
    p->next = NULL;
	return (p);
}
t_vars	*ft_lstlastenv(t_vars *lst)
{
	t_vars	*p;

	p = lst ;
	if (p == NULL)
		return (NULL);
	while (p->next != NULL)
	{
		p = p->next;
	}
	return (p);
}
void	add_envback(t_vars **lst, t_vars *new)
{
	t_vars	*p;

	p = ft_lstlastenv(*lst);
	if (p == NULL)
	{
		*lst = new;
		return ;
	}
		p->next = new;
}
t_vars *get_env(char **env)
{
  int i = 0;
  t_vars *vars;
  if(!env)
    return NULL
;  while(env[i])
  {
    add_envback(&vars, ft_envnew(ft_strdup(env[i])));
    i++;
  }
  return vars;
}
int ft_strlenCher(char *str,int a)
{
  int i  = 0 ;
  if(!str)
    return 0;
    while(str[i] != a && str[i])
        i++;
    return(i);
}
t_vars *get_declare(char **env)
{
  int i = 0;
  t_vars *vars;
  char *tmp;
  char *std1;
  char *std2;
  char **buffer;
  char *content;
int j = 0;
if(!env )
  return (NULL);

  while(env[i])
  {
        std1 = ft_substr(env[i],0,ft_strlenCher(env[i],'=')+1);
        std2 = ft_substr(env[i],ft_strlenCher(env[i],'=')+1,ft_strlen(env[i]));
        content = ft_strjoin(std1, "\"");
        tmp= content;
        content = ft_strjoin(content, std2);
        free(tmp);
        tmp= content;
        content = ft_strjoin(content, "\"");
        free(tmp);
        free(std2);
        free(std1);

        add_envback(&vars, ft_envnew(content));
        i++;
  }
  return (vars);
}

void ft_shell(t_vars *env, t_vars *declare)
{
  char *text;
    char path[100];
    t_tree *root;
    t_node *head;
  while(1)
    {
      //signal_gen(2);
      text = readline("minishell -> $> ");
      if(!text)
        break;
    if(text)
        add_history(text);
    head = token(text);
    root = bulid_tree(head, env , declare);
    }
}

int main(int ac ,char **argv ,char **env)
    {
    //rl_catch_signals = 0;
    t_vars *list = get_env(env);
    t_vars *declare = get_declare(env);

  // //  signal(SIGINT, &handle_sigint); // ctrl + c
  // //  signal(SIGQUIT, &handle_sigint); // ctrl+|
    if(ac != 1)
        return (1);
    ft_shell(list, declare);
 }