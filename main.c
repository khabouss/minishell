/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majdahim <majdahim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 14:09:04 by majdahim          #+#    #+#             */
/*   Updated: 2022/01/07 18:43:57 by majdahim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_execve(char *str_pips, t_list *env_list, char **env)
{
	char		*path;
	char		**args;

	path = getcwd(path, 0);
	args = get_args(str_pips, env_list);
	if (ft_strcmp("echo", args[0]) == 0)
		return (ft_echo(STDOUT_FILENO, args, env_list));
	else if (ft_strcmp("pwd", args[0]) == 0)
		return (ft_pwd(STDOUT_FILENO));
	else if (ft_strcmp("env", args[0]) == 0)
		return (ft_env(STDOUT_FILENO, env_list));
	else if (ft_strcmp("cd", args[0]) == 0)
		ft_cd(STDOUT_FILENO, args, env_list);
	else if (ft_strcmp("export", args[0]) == 0)
		return (ft_export(STDOUT_FILENO, args, env_list));
	else if (ft_strcmp("unset", args[0]) == 0)
		return (ft_unset(args, env_list));
	else if (ft_strcmp("exit", args[0]) == 0)
		return (ft_exit(STDOUT_FILENO, args));
	else
		ft_execve1(env_list, args, env);
    return (0);
}

t_list	*fill_env(char **env)
{
	t_list		*head;
	t_list		*tail;
	t_list		*temp;
	char		**s;
	int			i;

	head = NULL;
	tail = NULL;
	i = 0;
	while (env[i])
	{
		s = ft_split(env[i], '=');
		temp = malloc(sizeof(*temp));
		temp->env = env[i];
		temp->env_key = s[0];
		temp->env_value = s[1];
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

int	main(int argc, char **argv, char **env)
{
	char	*str;
	t_list	*env_list;

	env_list = fill_env(env);
	while (1)
	{
		str = readline(PROMPT);
		if (str == NULL)
			exit(0);
		add_history(str);
		if (fork() == 0)
			ft_execve(str, env_list, env);
		wait(NULL);
	}
	return (0);
}
