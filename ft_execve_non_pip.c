/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve_non_pip.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majdahim <majdahim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 01:59:54 by majdahim          #+#    #+#             */
/*   Updated: 2022/02/14 03:26:53 by majdahim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**fill_paramlist(char *path, char **args, int len, int len_filtered)
{
	int		i;
	int		j;
	char	**w;

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

void	ft_execve_non_pip(char *str_pips, t_list *env_list, char **env)
{
	char	*path;
	char	**args;
	int		args_len;
	int		args_len_filtered;
	int		i;
	int		updateout_fd;
	int		stdout_fd;
	int		stdin_fd;
	char	**_args;
	char	*pwd;

	stdout_fd = dup(1);
	stdin_fd = dup(0);
	i = 0;
	env = get_env(env_list);
	path = getcwd(path, 0);
	args = get_args(str_pips, env_list);
	args_len = 0;
	args_len_filtered = 0;
	while (args[args_len])
		args_len++;
	updateout_fd = update_out(args);
	if (args[0][0] == '\0')
	{
		dup2(stdout_fd, 1);
		dup2(stdin_fd, 0);
		return ;
	}
	if (updateout_fd == -1)
	{
		dup2(stdout_fd, 1);
		dup2(stdin_fd, 0);
		return ;
	}
	while (i < args_len)
	{
		if (args[i][0] != '\0')
			args_len_filtered++;
		i++;
	}
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
	if (ft_strcmp("echo", args[0]) == 0)
		ft_echo(STDOUT_FILENO, args);
	else if (ft_strcmp("exit", args[0]) == 0)
		ft_exit(1, args);
	else if (ft_strcmp("cd", args[0]) == 0)
		ft_cd(STDOUT_FILENO, args, env_list);
	else if (ft_strcmp("pwd", args[0]) == 0)
		ft_pwd(STDOUT_FILENO);
	else if (ft_strcmp("env", args[0]) == 0)
		ft_env(STDOUT_FILENO, env_list);
	else if (ft_strcmp("unset", args[0]) == 0)
		ft_unset(args, env_list);
	else if (ft_strcmp("export", args[0]) == 0)
		ft_export(STDOUT_FILENO, args, env_list);
	else
	{
		if (path == NULL)
		{
			ft_putstr(1, "Minishell: ");
			ft_putstr(1, args[0]);
			ft_putstr(1, ": command not found\n");
			dup2(stdout_fd, 1);
			dup2(stdin_fd, 0);
			return ;
		}
		_args = fill_paramlist(path, args, args_len, args_len_filtered);
		if (fork() == 0)
		{
			if (execve(path, _args, env) == -1)
			{
				ft_putstr(1, "Minishell: ");
				ft_putstr(1, args[0]);
				ft_putstr(1, ": No such file or directory\n");
				exit(EXIT_FAILURE);
			}
		}
		wait(NULL);
	}
	dup2(stdout_fd, 1);
	dup2(stdin_fd, 0);
	return ;
}
