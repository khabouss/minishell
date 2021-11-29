/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkhabous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 19:53:16 by tkhabous          #+#    #+#             */
/*   Updated: 2021/11/17 19:53:18 by tkhabous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



void ft_echo(int fd, char **args)
{
    int i;
    int check_n;

    int argc = ft_strlen2(args);
    int sp = 0;
    check_n = 0;

    i = 1;
    while(ft_strcmp("-n",args[i]) == 0)
    {
        sp = 1;
        i++;
    }
    while(i < argc)
    {
        ft_putstr(fd, args[i]);
        i++;
        if(args[i] && args[i][0] != '\0')
            ft_putstr(fd, " ");
    }
    if(sp == 0)
        ft_putstr(fd, "\n");
}

t_list    *fill_env(char **env)
{
    t_list *head = NULL;
    t_list *tail = NULL;
    int i;
    i = 0;
    t_list *temp;
    char **s;
    while (env[i])
    {
        s = ft_split(env[i],'=');
        temp = malloc(sizeof(*temp));
        temp->env = env[i];
        temp->env_key = s[0];
        temp->env_value= s[1];
        temp->next = NULL;
        if (!head)
        {
            head = temp;
            tail = head;
        }
        else
        {
            tail->next = temp;
            tail = temp;
        }
        i++;
    }
    return (head);
}

void    ft_env(int fd, t_list *env_list)
{
    t_list *current = env_list;
    while(current != NULL)
    {
        ft_putstr(fd, current->env_key);
        ft_putstr(fd, "=");
        ft_putstr(fd, current->env_value);
        ft_putstr(fd, "\n");
        current = current->next;
    }
}
void ft_pwd(int fd)
{
    char *r = NULL;
    ft_putstr(fd, getcwd(r,1));
    ft_putstr(fd, "\n");
}

char* searchch(char *word,char *changed,t_list *env_list)
{
    t_list *current = env_list;
    while(current != NULL)
    {
        if(ft_strcmp(current->env_key,word) == 0)
        {
            current->env_value = changed;
            break;
        }
        current = current->next;
    }

    return(current->env_value);
}

void    ft_cd(int fd, char **args,char *path, t_list *env_list)
{
    char *pwd = NULL;

    if(chdir(args[1])!= 0)
        ft_putstr(fd, "Error\n");
    
    pwd = getcwd(pwd,0);

    searchch("PWD",pwd,env_list);
    // ft_putstr("\n");
    
    // searchch("OLDPWD",path,env_list);
    // ft_putstr("\n");
}


void    print_list(int fd, t_list *env_list)
{
    t_list *current = env_list;
    while(current != NULL)
    {
        ft_putstr(fd, "declare -x ");
        ft_putstr(fd, current->env_key);
        ft_putstr(fd, "=\"");
        ft_putstr(fd, current->env_value);
        ft_putstr(fd, "\"\n");
        current = current->next;
    }
}

t_list *add_content(char **content)
{
    t_list *lst;
    if(!(lst = malloc(sizeof(t_list))))
        return (NULL);
    lst->env_key = content[0];
    lst->env_value = content[1];
    lst->next = NULL;

    return(lst);
}

void	ft_lstadd_back(t_list **env_list, t_list *new)
{
	t_list		*begin;

	if (env_list && (*env_list) && new)
	{
		begin = (*env_list);
		if (begin == NULL)
			(*env_list) = new;
		else
		{
			while (begin->next)
				begin = begin->next;
			begin->next = new;
		}
	}
}

void    addto_list(char *args,t_list *env_list)
{

   t_list *current = env_list;
   char **s = ft_split(args,'=');
   int b = 0;
    while(current != NULL)
    {
        if(ft_strcmp(current->env_key,s[0]) == 0)
        {
            current->env_value = s[1];
            b=1;
            break;
        }
        current = current->next;
    }
    if(!b)
        ft_lstadd_back(&env_list,add_content(s));
}

void ft_export(int fd, char **args,t_list *env_list)
{
    int i = 0;
    if(args)
    {
         while(args[++i])
            addto_list(args[i],env_list);
    }
    if(!args[1])
        print_list(fd, env_list);
}


void       delet_v_env(t_list *env_list,char *argv)
{
    t_list *current = env_list;
    t_list *temp, *prev;
    char **s = ft_split(argv,'=');
    if ((ft_strcmp(current->env_key, s[0]) == 0) && current != NULL)
    {
        temp = current->next;
        free(current);
        current = NULL;
        env_list = temp;
        write(1, "--\n", 3);
        return ;
    }
    while(current != NULL)
    {
        if(ft_strcmp(current->env_key,s[0]) == 0)
        {
            temp = current->next;
            prev->next = temp;
            free(current);
            break ;
        }
        prev = current;
        current = current->next;
    }
}


void    ft_unset(char **args,t_list *env_list)
{
    int i = -1;
    if(args)
        while(args[++i])
            delet_v_env(env_list,args[i]);
}


char*     check_fill_path(t_list *env_list,char **args)
{
    int     i;
    char    **w;
    char    *s;
    int     fd;
    i = 0;
    fd = 0;
	s = NULL;
    t_list *current = env_list;
    while (current != NULL)
    {
        if (!ft_strcmp(current->env_key, "PATH"))
        {
            w = ft_split(current->env_value, ':');
            while (w[i])
            {
                s = ft_strjoin(w[i], "/");
                s = ft_strjoin(s, args[0]);
                fd = open(s, O_RDONLY);
                if (fd > 0)
                {
					close(fd);
                    return (s);
                }
				close(fd);
				free(s);
                i++;
            }
        }
        current = current->next;
    }
    return (0);
}

char    **fill_paramlist(char *path,char **args, int len, int len_filtered)
{
    int     i;
    int     j;
    char    **w;

    i = 0;
    j = 0;
    w = malloc(sizeof(char *) * (len_filtered + 1));
    while (i < len)
    {
        if (args[i][0] != '\0')
        {
            w[j] = ft_strdup(args[i]);
            j++;
        }
        i++;
    }
    w[j] = NULL;
    return (w);
}

int    ft_heredoc(char **args, int i, int old)
{
    if (old != -1)
        dup2(old, 0);
    char *eof;
    char *input;
    char *buff;
    char *temp;
    int fd;


    if (args[i][2] != '\0')
        eof = ft_substr(args[i], 2, ft_strlen(args[i]) - 2);
    else
    {
        eof = ft_strdup(args[i + 1]);
        args[i+1][0] = '\0';
    }
    input = NULL;
    buff = "";
    fd = open("heredoc_temp", O_CREAT | O_RDWR | O_TRUNC, 0666);
    while (ft_strcmp(input, eof) != 0)
    {
        input = readline("> ");
        if (ft_strcmp(input, eof) != 0)
        {
            buff = ft_strjoin(buff, input);
            buff = ft_strjoin(buff, "\n");
        }
    }
    write(fd, buff, ft_strlen(buff) - 1);
    if (ft_strlen(buff) > 1)
        write(fd, "\n", 1);
    close(fd);
    args[i][0] = '\0';
    fd = open("heredoc_temp", O_RDWR, 0666);
    int old_stdin = dup(STDIN_FILENO);
    dup2(fd, STDIN_FILENO);
    return (old_stdin);
}

int num_of_cmds(char *str)
{
    int i;
    int cmds;

    i = 0;
    cmds = 0;
    while (str[i] != '\0')
    {
        while (str[i] != '\0' && str[i] != ' ' && str[i] != '\"' && str[i] != '\'')
            i++;
        if (str[i] == ' ' || str[i] == '\0')
        {
            if (i != 0)
                cmds++;
            while (str[i] == ' ')
                i++;
        }
        if (str[i] == '\"')
        {
            i++;
            while (str[i] && str[i] != '\"')
                i++;
            if (str[i] == '\0')
                return (-1);
            if (str[i] == '\"')
                i++;
            if (str[i] == '\0')
                cmds++;
        }
        if (str[i] == '\'')
        {
            i++;
            while (str[i] && str[i] != '\'')
                i++;
            if (str[i] == '\0')
                return (-1);
            if (str[i] == '\'')
                i++;
            if (str[i] == '\0')
                cmds++;
        }
    }
    return cmds;
}

int     get_start(char *str, int i)
{
    int j;

    j = i;
    while (j)
    {
        if (str[j] && str[j] == ' ')
            return (j);
        j--;
    }
    return (j);
}

char **get_args(char *str)
{
    char **args;
    int j;
    int i;
    int index[2];

    i = 0;
    j = 0;
    args = (char **)malloc(num_of_cmds(str) * sizeof(char *));
    while (str[i] != '\0')
    {
        while (str[i] != '\0' && str[i] != ' ' && str[i] != '\"' && str[i] != '\'')
            i++;
        if (str[i] == ' ' || str[i] == '\0')
        {
            if (i != 0)
                args[j++] = ft_substr(str, get_start(str, i), i);
            while (str[i] == ' ')
                i++;
        }
        if (str[i] == '\"')
        {
            i++;
            while (str[i] && str[i] != '\"')
                i++;
            if (str[i] == '\0')
                return (NULL);
            if (str[i] == '\"')
                i++;
            if (str[i] == '\0')
                args[j++] = ft_substr(str, get_start(str, i), i);
        }
        if (str[i] == '\'')
        {
            i++;
            while (str[i] && str[i] != '\'')
                i++;
            if (str[i] == '\0')
                return (NULL);
            if (str[i] == '\'')
                i++;
            if (str[i] == '\0')
                args[j++] = ft_substr(str, get_start(str, i), i);
        }
    }
    
    return args;
}

int    update_out(char **args)
{
    int i;
    char *file_name;
    int fd;
    int is_double;
    int in;
    int old_stdin;

    in = -1;

    i = 0;
    old_stdin = -1;
    while (args[i])
    {
        is_double = 0;
        if (args[i][0] == '>')
        {
            in = 0;
            if (args[i][1] == '>')
                is_double = 1;
            if (args[i][1 + is_double] != '\0')
                file_name = ft_substr(args[i], 1 + is_double, ft_strlen(args[i]) - 1 - is_double);
            else
            {
                file_name = ft_strdup(args[i+1]);
                args[i+1][0] = '\0';
            }
            if (is_double == 0)
                fd = open(file_name, O_CREAT | O_RDWR | O_TRUNC , 0666);
            else
                fd = open(file_name, O_CREAT | O_RDWR | O_APPEND , 0666);
            args[i][0] = '\0';
        }
        if (args[i][0] == '<' && args[i][1] != '<')
        {
            in = 1;
            if (args[i][1] != '\0')
                file_name = ft_substr(args[i], 1, ft_strlen(args[i]) - 1);
            else
            {
                file_name = ft_strdup(args[i+1]);
                args[i+1][0] = '\0';
            }
            fd = open(file_name, O_RDWR, 0666);
            if (fd == -1)
            {
                printf("minishell: %s: No such file or directory\n", file_name);
                return (-1);
            }
            args[i][0] = '\0';
        }
        if (args[i][0] == '<' && args[i][1] == '<')
            old_stdin = ft_heredoc(args, i, old_stdin);
        i++;
    }
    if (in == 0)
        dup2(fd, STDOUT_FILENO);
    if (in == 1)
        dup2(fd, STDIN_FILENO);
    return (1);
}

void    ft_execve(char *str_pips, t_list *env_list, char **env)
{
    char *path;
    char **args;
    int args_len;
    int args_len_filtered;
    int i = 0;

    path = getcwd(path,0);
    args = ft_split(str_pips, ' ');
    args_len = 0;
    args_len_filtered = 0;
    while (args[args_len])
        args_len++;
    if (update_out(args) == -1)
        exit(EXIT_FAILURE);
    while (i < args_len)
    {
        if (args[i][0] != '\0')
            args_len_filtered++;
        i++;
    }
    if (ft_strcmp("echo",args[0]) == 0)
        ft_echo(STDOUT_FILENO, args);
    else if (ft_strcmp("cd",args[0]) == 0)
        ft_cd(STDOUT_FILENO, args,path,env_list);
    else if (ft_strcmp("pwd",args[0]) == 0)
        ft_pwd(STDOUT_FILENO);
    else if (ft_strcmp("env",args[0]) == 0)
        ft_env(STDOUT_FILENO, env_list);
    else if (ft_strcmp("unset",args[0]) == 0)
        ft_unset(args,env_list);
    else if (ft_strcmp("export",args[0]) == 0)
        ft_export(STDOUT_FILENO, args,env_list);
    else
    {
        path = check_fill_path(env_list, args);
        char **_args = fill_paramlist(path, args, args_len, args_len_filtered);
        execve(path, _args, env);   
    }
    exit(EXIT_SUCCESS);
}

int**    ft_pipe(int pips)
{
    int **pipe_fd;
    int i;

    pipe_fd = (int **)malloc(pips * sizeof(int *));
    i = -1;
    while (++i < pips)
    {
        pipe_fd[i] = (int *)malloc(2 * sizeof(int));
        pipe(pipe_fd[i]);
    }
    return (pipe_fd);
}


void    ft_close(int i, int pips, int **pipe_fd)
{
    int j;

    j = 0;
    while (j < pips)
    {
        if (j != i - 1)
            close(pipe_fd[j][0]);
        if (j != i)
            close(pipe_fd[j][1]);
        j++;
    }
}

void    ft_free2d(int **arr, int i)
{
    while (i--)
        free(arr[i]);
    free(arr);
}

void handle_pipe(char **str_pips, t_list *env_list, int pips, char **env)
{
    int **pipe_fd;
    int status;
    int i;

    pipe_fd = ft_pipe(pips);
    i = -1;
    while (++i < pips + 1)
    {
        if (fork() == 0)
        {
            ft_close(i, pips, pipe_fd);
            if (i != 0)
                dup2(pipe_fd[i - 1][0], STDIN_FILENO);
            if (i != pips)
                dup2(pipe_fd[i][1], STDOUT_FILENO);
            ft_execve(str_pips[i], env_list, env);
            ft_putstr(STDOUT_FILENO, 0);
            ft_close(-1, pips, pipe_fd);
        }
    }
    ft_close(-1, pips, pipe_fd);
    while (wait(&status) > 0);
    ft_free2d(pipe_fd, pips);
}

int main(int argc, char **argv, char **env)
{

    char *str;
    char **str_pip;
    t_list *env_list;
    int pips;
    int i;

    env_list = fill_env(env);
    while(1)
    {
        str = readline(PROMPT);
        pips = 0;
        i = 0;
        add_history(str);
        while (str[i] != '\0')
        {
            if (str[i] == '|')
                pips++;
            i++;
        }
        if (pips)
        {
            str_pip = ft_split(str, '|');
            handle_pipe(str_pip, env_list, pips, /* NEW */env);
        }
        else
        {
            if (fork() == 0)
                ft_execve(str, env_list, /* NEW */env);
            wait(NULL);    
        }
        
    }
    return (0);
}