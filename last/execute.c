#include "minishell.h"


void ft_export(char **str, t_vars *env,  t_vars *declare)
{
    int i = 1;
    char *tmp;
    char *content;
    char **line;
   //str = ft_split(*str, ' ');
   if(str[1] == NULL)
   {
        while(declare != NULL)
        {
            printf("%s\t", "declare -x");
            printf("%s\n", declare->data);
            declare = declare->next;
            
        }
   }
   else if(str[1][0] == '=')
   {
       printf("minshell: export: `%s': not a valid identifier;", str[1]);     
   }
   else
   {
        while(str[i])
        {
            if(ft_strchr(str[i], '=') == 1)
            {
                add_envback(&env, ft_envnew(str[i]));
                if(str[i][ft_strlen(str[i]) - 1] == '=')
                    add_envback(&declare, ft_envnew(ft_strjoin(str[i], "\"\""))); 
                else
                {
                    line = ft_split(str[i], '=');
                    tmp = content;
                    content = ft_strjoin(str[0], "=");
                    //free(tmp);
                    tmp = content;
                    content = ft_strjoin(content, "\"");
                    //free(tmp);
                    tmp = content;
                    if(line[1][0] =='\'' && line[1][ft_strlen(line[1] - 2)] == '\'')
                        content = ft_strjoin(content, ft_substr(line[1], 1, ft_strlen(line[1] - 2)));
                    else
                         content = ft_strjoin(content, line[1]);
                    //free(tmp);
                    tmp = content;
                    content = ft_strjoin(content, "\"");
                    //free(tmp);    
                      add_envback(&declare, ft_envnew(content)); 
                }
            }
            else
            {
                
               add_envback(&declare, ft_envnew(str[i])); 
            }
            i++;
        }
   }
   
}

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
char **ft_env(t_vars *vars)
{
    int i = 0;
    t_vars *tmp=vars;
    char **ourenv = NULL;
    while(vars != NULL)
    {
        i++;
        vars = vars->next;
    }
    ourenv = ft_calloc(sizeof(char *), i);
    i = 0;

    while(tmp != NULL)
    {
        ourenv[i] = tmp->data;
        i++;
        tmp = tmp->next;
    }
    return(ourenv);   
};

void cd (char *p)
{
    int a;
    a = chdir(p);
    if(a == -1)
        printf("(%s) No such file or directory\n",p);
}

char *delimet(char *l)
{
    int i = 0;
    while(ft_strchr(" <>",l[i]) != 0)
        i++;
    return(l +i);
}

 void ft_close(int **fd, int len)
    {
        int i = 0;
        while(i < len)
        {
            close(fd[i][0]);
            close(fd[i][1]);
            i++;
        }
    }


void buildInChild(char **cmd,t_vars *env,t_vars *declare)
{
    char *path;
    if(ft_strcmp("echo",cmd[0]) == 0)
        echo(cmd);
    else if(ft_strcmp("pwd",cmd[0]) == 0)
        {
            path = ft_calloc(sizeof(char), 1024);
            if(getcwd(path, 50) != NULL) 
                printf("%s\n", path);
            else
                printf("%s", "error");
        }
    else if(ft_strcmp(cmd[0],"export") == 0)
                ft_export(cmd,env,declare);
    exit(0);
}

void cmd1(char **cmd, t_vars *env,t_vars *declare)
{
    char *path;
    char **split_path;
    char **envs;
    char *tmp;
    char *joinCmd;
    int i  = 0;

    if(ft_strcmp(cmd[0],"echo") == 0 || ft_strcmp(cmd[0],"pwd") == 0 || ft_strcmp(cmd[0],"export") == 0 )
    {
        // write(2,"hamza\n",6);
        buildInChild(cmd,declare,env);
    }
    envs = ft_env(env);
    execve(cmd[0],cmd,envs);
    path = get_env_arr("PATH",env);
    split_path =ft_split(path,':');
    if(split_path != NULL)
    {
        while(split_path[i])
        {
            tmp = ft_strjoin(split_path[i],"/");
            joinCmd =ft_strjoin(tmp,cmd[0]);
            free(tmp);
            execve(joinCmd,cmd,envs);
            free(joinCmd);
            i++;
        }
        free2d(split_path);
    }
    write(2,"IH : command not found\n",24);
    free2d(cmd);
        
}

void dups(char **deriction,char **heredoctable)
{
   //check_in_out(deriction);
   int i = 0;
   int fd;
   int fd1;
   int fd2;
   char *inFile = NULL;
   char *outFile = NULL;
   char *outAppend = NULL;
   char *heredoc =NULL;
   while(deriction[i])
   {

        if(ft_search(deriction[i],'<'))
        {
            if(ft_search(deriction[i],'<') == 2)
                heredoc = delimet(deriction[i]);
            else
            {
                inFile = delimet(deriction[i]);
                heredoc = NULL;
                fd = open(inFile,O_RDONLY);
                if(fd == -1)
                    exit(write(2,"No such file or directory\n",27));
                close(fd);
            }
                    
                
        }
        else if(ft_search(deriction[i],'>'))
        {
            if(ft_search(deriction[i],'>') == 2)
            {
                outAppend = delimet(deriction[i]);
            }
            else
            {
                outFile = delimet(deriction[i]);
                 close(open(outFile,O_CREAT|O_TRUNC,0644));
                outAppend = NULL;
            } 
        }
        i++;
   }
    i = 0;
   if(heredoc != NULL)
   {
        fd1 = open("/tmp/heredoc",O_WRONLY|O_CREAT|O_TRUNC,0700);
        while(heredoctable[i])
            ft_putstr(heredoctable[i++],fd1);
        close(fd1);
        fd1 = open("/tmp/heredoc",O_RDONLY);
        dup2(fd1,0);

   }
   else if(inFile != NULL)
   {
        fd1 = open(inFile,O_RDONLY,0644);
        if(fd1 == -1)
            exit(write(2,"No such file or directory",27));
        dup2(fd1,0);
        
   }
   if(outAppend != NULL)
   {
        fd2 = open(outAppend,O_WRONLY| O_CREAT|O_APPEND,0644);
        dup2(fd2,1);
   }
   else if(outFile != NULL)
   {
        fd2 = open(outFile,O_CREAT|O_WRONLY|O_TRUNC,777);
        if(fd2 == -1)
            write(2,"filed\n",6);
        dup2(fd2,1);
   }
}

void buildInParent(t_data *var,int i,t_vars *env,  t_vars *declare)
{
    if(ft_strcmp(var->cmd[i][0],"cd") == 0)
        {
            if(var->op[i] != NULL)
            {
                if(ft_strncmp(var->op[i]->type,"OP_PIPE",7) != 0)
                        cd(var->cmd[i][1]);
            }else
                cd(var->cmd[i][1]);
        }
    else if(ft_strcmp(var->cmd[i][0],"exit") == 0)
        {
            if(var->op[0] == NULL)
                exit(0);
        }
    else if(ft_strcmp(var->cmd[i][0],"export") == 0)
    {
            if(var->op[0] == NULL)
                ft_export(var->cmd[i],env,declare);
    }
    // else if(ft_strcmp(var->cmd[i][0],"unset") == 0)
    //     {
    //         if(var->op[i] != NULL)
    //         {
    //             if(ft_strncmp(var->op[i]->type,"OP_PIPE",7) != 0)
    //                     ft_unset();
    //         }else
    //             ft_unset();
    //     }
}

void execute(t_data *var,t_vars *env,  t_vars *declare)
{
    int i ;
    int id ;
    int **fd;
    int lenPipe;
    int pipeIncrement = 0;
    lenPipe = 0;
    i = 0;
    while(var->op[i])
    {
        if(ft_strncmp(var->op[i]->type,"OP_PIPE",7) == 0)
            lenPipe++;
        i++;
    }
    int len  = i ;
    fd = malloc(sizeof(int*)*lenPipe);
    i = 0;
    while(i < lenPipe)
    {
        fd[i] = malloc(sizeof(int)* 2);
        pipe(fd[i]);
        i++;
    }
     //write(1,"hamza\n",6);
    i = 0;
    while(var->cmd[i])
    {
        if(ft_strcmp(var->cmd[i][0],"cd") == 0 || ft_strcmp(var->cmd[i][0],"exit") == 0 ||(ft_strcmp(var->cmd[i][0],"export") == 0 &&  var->cmd[i][1] != NULL)|| ft_strcmp(var->cmd[i][0],"unset") == 0 )
            buildInParent(var,i,env,declare);
        else 
        {
            id =fork();
            if(id == 0)
            {
                if(var->op[i] != NULL)
                    if(ft_strncmp(var->op[i]->type,"OP_PIPE",7) == 0)
                        dup2(fd[pipeIncrement][1],1);
                    
                if(var->deriction[i] != NULL)
                    dups(var->deriction[i],var->heredoc[i]);

                if(i - 1 >= 0 && pipeIncrement > 0)
                    if(ft_strncmp(var->op[i - 1]->type,"OP_PIPE",7) == 0)
                            dup2(fd[pipeIncrement - 1][0],0);

                ft_close(fd, lenPipe);
                cmd1(var->cmd[i],env,declare);
                exit(0);
            }
                if(var->op[i] != NULL)
                    if(ft_strncmp(var->op[i]->type,"OP_PIPE",7) == 0)
                        pipeIncrement++;
        }
        i++;
    }
    while((wait(0)) != -1)
        ft_close(fd, lenPipe);

}