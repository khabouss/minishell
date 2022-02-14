/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majdahim <majdahim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 01:49:09 by majdahim          #+#    #+#             */
/*   Updated: 2022/02/14 03:05:23 by majdahim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_execve(char *str_pips, t_list *env_list)
{
	char	*path;
	char	**env;
	char	**args;
	int		args_len;
	int		i;
	t_list	*head;
	char	**args1;
	pid_t	pid;
	int		status;
	char	*pwd;
	char	*str;
	int		u;
	int		r;

	env = get_env(env_list);
	i = 0;
	path = getcwd(path, 0);
	args = get_args(str_pips, env_list);
	args_len = 0;
	while (args[args_len] != NULL)
		args_len++;
	r = update_out(args);
	if (r == -1)
		return ;
	if (args == NULL || args[0] == '\0')
		return ;
	if (ft_strcmp("exit", args[0]) == 0)
		ft_exit(1, args);
	if (ft_strcmp("export", args[0]) == 0)
		return (ft_export(STDOUT_FILENO, args, env_list));
	if (ft_strcmp("unset", args[0]) == 0)
		return (ft_unset(args, env_list));
	if (ft_strcmp("cd", args[0]) == 0)
		return (ft_cd(STDOUT_FILENO, args, env_list));
	if (ft_strcmp("pwd", args[0]) == 0)
		return (ft_pwd(STDOUT_FILENO));
	if (ft_strcmp("env", args[0]) == 0)
		return (ft_env(STDOUT_FILENO, env_list));
	if (ft_strcmp("echo", args[0]) == 0)
		return (ft_echo(STDOUT_FILENO, args));
	path = check_fill_path(env_list, args);
	if (ft_strchr(args[0], '/'))
	{
		path = args[0];
		if (args[0][0] == '.' && args[0][1] == '.')
		{
			pwd = NULL;
			if (chdir(args[0]) != 0)
				ft_putstr(1, "Error\n");
			pwd = getcwd(pwd, 0);
			searchch("PWD", pwd, env_list);
			searchch("OLDPWD", path, env_list);
		}
	}
	if (path == NULL)
	{
		ft_putstr(1, "Minishell: ");
		ft_putstr(1, args[0]);
		ft_putstr(1, ": command not found\n");
		return ;
	}
	u = 0;
	str = "";
	while (u < args_len)
	{
		str = ft_strjoin(str, args[u]);
		str = ft_strjoin(str, " ");
		u++;
	}
	args = get_args(str, env_list);
	if (execve(path, args, env))
	{
		if (args[0][0] != '.' && args[0][1] != '.')
		{
			ft_putstr(1, "Minishell: ");
			ft_putstr(1, args[0]);
			ft_putstr(1, ": No such file or directory\n");
		}
	}
	exit(EXIT_SUCCESS);
}
