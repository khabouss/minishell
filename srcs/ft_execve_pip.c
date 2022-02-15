/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve_pip.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majdahim <majdahim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 02:36:40 by majdahim          #+#    #+#             */
/*   Updated: 2022/02/15 18:39:30 by majdahim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_close(int i, int pips, int **pipe_fd)
{
	int		j;

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

void	ft_execve_pip(char *str_pips, t_list *env_list)
{
	char	*path;
	char	**args;
	int		args_len;
	int		args_len_filtered;
	int		i;
	int		stdout_fd;
	int		stdin_fd;
	char	**env;
	char	*pwd;
	char	**_args;
	char	*str;

	str = "";
	path = NULL;
	i = 0;
	g_sig[1] = 0;
	env = get_env(env_list);
	stdout_fd = dup(1);
	stdin_fd = dup(0);
	path = getcwd(path, 0);
	args = ft_split(str_pips, ' ');
	if (update_out(args) == -1)
	{
		dup2(stdout_fd, 1);
		dup2(stdin_fd, 0);
		exit(g_sig[1]);
	}
	while (args[i] != NULL)
	{
		str = ft_strjoin(str, args[i]);
		str = ft_strjoin(str, " ");
		i++;
	}
	str = ft_strtrim(str, " ");
	args = get_args(str, env_list);
	args_len = 0;
	args_len_filtered = 0;
	while (args[args_len])
		args_len++;
	if (args[0][0] == '\0')
	{
		dup2(stdout_fd, 1);
		dup2(stdin_fd, 0);
		exit(EXIT_FAILURE);
	}
	i = 0;
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
			{
				ft_putstr(2, "No such file or directory\n");
				g_sig[1] = 127;
				exit(g_sig[1]);
			}
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
		ft_cd(args, env_list);
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
			ft_putstr(2, "Minishell: ");
			ft_putstr(2, args[0]);
			ft_putstr(2, ": command not found\n");
			dup2(stdout_fd, 1);
			dup2(stdin_fd, 0);
			g_sig[1] = 127;
			exit(g_sig[1]);
		}
		_args = fill_paramlist(args, args_len, args_len_filtered);
		if (execve(path, _args, env) == -1)
		{
			ft_putstr(2, "Minishell: ");
			ft_putstr(2, args[0]);
			ft_putstr(2, ": No such file or directory\n");
			g_sig[1] = 127;
			exit(g_sig[1]);
		}
	}
	dup2(stdout_fd, 1);
	dup2(stdin_fd, 0);
	exit(g_sig[1]);
}
