#include "minishell.h"


void echo(char **cmd)
{
    int i = 1;
    int newline = 0;
    if(cmd[i] != NULL)
        if(ft_strcmp("-n",cmd[i]) == 0)
                newline = i++;
    while(cmd[i])
    {
        printf("%s",cmd[i]);
        i++;
        if(cmd[i] != NULL)
            printf(" ");
    }
    if(newline == 0)
        printf("\n");
    
}
void cd (char *p)
{
    int a;
    a = chdir(p);
    if(a == -1)
        printf("(%s) No such file or directory\n",p);
}
void ft_env(char **env)
{
    int i = 0;
    while(env[i])
    {
        printf("%s\n",env[i]);
        
        i++;
    }
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
char **ft_export(char **env,char *p)
{
    int i = 0;
    int len =ft_strlen2d(env);
    while(env[i])
    {
        if(ft_strnstr(env[i],p,ft_strlen(p)) != NULL)
        {
            env[i] = p;
            break;
        }
        i++;
    }
    if(env[i] == NULL)
        env = ft_join2d(env,p);
    return env;
}

// int main(int ac,char **argv,char **env)
// {
//     env = ft_export(env,"iss");
//     ft_env(env);
// }