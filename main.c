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

int sig;


void    checkdollar(char *vrenv,t_list *env_list)
{
    t_list *current = env_list;
    while(current != NULL)
    {
        if(ft_strcmp(current->env_key,vrenv) == 0)
        {
            ft_putstr(current->env_value);
            // ft_putstr("\n");
            break;
        }
        current = current->next;
    }
}

void ft_echo(char **args,t_list *env_list)
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
    while(i < argc && args[i][0] != '|')
    {
        if(args[i][0] == '$')
        {
            int len = ft_strlen(args[i]);
            char *vrenv = ft_substr(args[i],1,len);
            checkdollar(vrenv,env_list);
        }
        else
            ft_putstr(args[i]);
        i++;
        if(args[i])
            ft_putstr(" ");
    }
    if(sp == 0)
        ft_putstr("\n");
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

void    ft_env(t_list *env_list)
{
    t_list *current = env_list;
    while(current != NULL)
    {
        ft_putstr(current->env_key);
        ft_putstr("=");
        ft_putstr(current->env_value);
        ft_putstr("\n");
        current = current->next;
    }
}
void ft_pwd()
{
    char *r = NULL;
    ft_putstr(getcwd(r,1));
    ft_putstr("\n");
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

void    ft_cd(char **args,char *path, t_list *env_list)
{
    char *pwd = NULL;

    if(chdir(args[1])!= 0)
        ft_putstr("Error\n");
    
    pwd = getcwd(pwd,0);

    searchch("PWD",pwd,env_list);
    // ft_putstr("\n");
    
    searchch("OLDPWD",path,env_list);
    // ft_putstr("\n");
}


void    print_list(t_list *env_list)
{
    t_list *current = env_list;
    while(current != NULL)
    {
        ft_putstr("declare -x ");
        ft_putstr(current->env_key);
        ft_putstr("=\"");
        ft_putstr(current->env_value);
        ft_putstr("\"\n");
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

void ft_export(char **args,t_list *env_list)
{
    int i = 0;
    if(args)
    {
         while(args[++i])
            addto_list(args[i],env_list);
    }
    if(!args[1])
        print_list(env_list);
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


int     check_fill_path(t_list *head,t_list *env_list,char **args)
{
    int     i;
    char    **w;
    char    *s;
    int     fd;
    // t_list *head;
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
                    head->path = s;
					close(fd);
                    return (1);
                }
				close(fd);
				free(s);
                i++;
            }
        }
        current = current->next;
    }
	// node->path = NULL;
    return (0);
}

char    **fill_paramlist(t_list *head,char **args)
{
    int     i;
    char    **w;

    i = 0;
    w = malloc(sizeof(char *) * 3);
    w[0] = ft_strdup(head->path);
    if (args[1])
        w[1] = ft_strdup(args[1]);
    else
        w[1] = NULL;
    return (w);
}

void    ft_exec(t_list *head,char **args)
{
    int pid = fork();
    int status;
    sig =2;
   if (pid == -1)
   {
        ft_putstr("Error\n");
        exit(0);
    }
    if(pid == 0)
    {
        execve(head->path,fill_paramlist(head,args), NULL);
        sleep(2);
        exit(EXIT_SUCCESS);
    }
    wait(&status);
}

void handle(char **args, t_list *env_list)
{
    int i;
    t_list *head;
    i = 0;
    char *path = NULL;
    path = getcwd(path,0);
    if (ft_strcmp("echo",args[i]) == 0)
        ft_echo(args,env_list);
    else if (ft_strcmp("cd",args[i]) == 0)
        ft_cd(args,path,env_list);
    else if (ft_strcmp("pwd",args[i]) == 0)
        ft_pwd();
    else if (ft_strcmp("env",args[i]) == 0)
        ft_env(env_list);
    else if (ft_strcmp("unset",args[i]) == 0)
        ft_unset(args,env_list);
    else if (ft_strcmp("export",args[i]) == 0)
        ft_export(args,env_list);
    else
    {
        check_fill_path(head,env_list,args);
        ft_exec(head,args);
    }

}
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void handle_int(int sig_num)
{
    rl_on_new_line();
    ft_putstr("\n");
    rl_replace_line("", 0);
    rl_redisplay();
} 

void handle_int1(int sig_num)
{
    if(sig == 2)
        ft_putstr("Quit: 3\n");
} 

int main(int argc, char **argv, char **env)
{
    char *str;
    char **args;
    t_list *env_list;
    env_list = fill_env(env);

    while(1)
    {
	signal(SIGINT,handle_int);
	signal(SIGQUIT,handle_int1);
        str = readline("PROMPT> ");
        if(str == NULL)
            exit(0);
        add_history(str);
        args = ft_split(str,' ');
        handle(args, env_list);
    }
    return (0);
}