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

void handle(char **args)
{
    int i;

    i = 1;
    if (ft_strcmp("echo",args[i]) == 0)
    {
        if (ft_strcmp("-n",args[i+1]) == 0)
            ft_echo(args[i+2], 1);
        else
            ft_echo(args[i+1], 0);
    }
    if (ft_strcmp("cd",args[i]) == 0)
        ft_cd(args[i+1]);
    
    if (ft_strcmp("pwd",args[i]) == 0)
        ft_pwd();
    
    if (ft_strcmp("env",args[i]) == 0)
        ft_env();

    if (ft_strcmp("unset",args[i]) == 0)
        ft_unset(args);

    if (ft_strcmp("export",args[i]) == 0)
    {
        if (args[i + 1])
        {
            if (args[i + 1][0] == '|')
                ft_export("dump", 0);
            else
                ft_export(args[i + 1], 1);
        }
        else
            ft_export("dump", 0);
    }
}


int main(int argc, char **argv, char **env)
{
    (void)argc;
    (void)env;
    

    char *str;
    while(1)
    {
        str = readline("PROMPT> ");
        add_history(str);
        handle(argv);
    }

    return (0);
}