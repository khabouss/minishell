/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve_non_pip.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majdahim <majdahim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 01:59:54 by majdahim          #+#    #+#             */
/*   Updated: 2022/02/16 04:07:00 by majdahim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**fill_paramlist(char **args, int len, int len_filtered)
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
	char	**args_tmp;
	char	*pwd;
	char	*str;
	char	*tmp;

	str = "";
	path = NULL;
	g_sig[1] = 0;
	stdout_fd = dup(1);
	stdin_fd = dup(0);
	i = 0;
	env = get_env(env_list);
	args_tmp = ft_split(str_pips, ' ');
	updateout_fd = update_out(args_tmp);
	while (args_tmp[i] != NULL)
	{
		tmp = ft_strjoin(str, args_tmp[i]);
		if (str[0] != '\0')
			free(str);
		str = ft_strjoin(tmp, " ");
		free(tmp);
		i++;
	}
	free_t2(args_tmp);
	args = get_args(str, env_list);
	free(str);
	args_len = 0;
	args_len_filtered = 0;
	while (args[args_len])
		args_len++;
	if (args[0][0] == '\0')
	{
		dup2(stdout_fd, 1);
		dup2(stdin_fd, 0);
		free(env);
		return ;
	}
	if (updateout_fd == -1)
	{
		dup2(stdout_fd, 1);
		dup2(stdin_fd, 0);
		free(env);
		return ;
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
				free(env);
				return ;
			}
			pwd = getcwd(pwd, 0);
			searchch("PWD", pwd, env_list);
			searchch("OLDPWD", path, env_list);
		}
	}
	if (ft_strcmp("echo", args[0]) == 0)
		ft_echo(args);
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
			free(env);
			return ;
		}
		int fdtry = open(path, O_RDONLY);
		if (fdtry < 0)
		{
			ft_putstr(2, "Minishell: ");
			ft_putstr(2, args[0]);
			ft_putstr(2, ": No such file or directory\n");
			g_sig[1] = 127;
			free(env);
			free(path);
			return ;
		}
		_args = fill_paramlist(args, args_len, args_len_filtered);
		g_sig[0] = 2;
		if (fork() == 0)
		{
			if (execve(path, _args, env) == -1)
			{
				exit(EXIT_FAILURE);
			}
		}
		wait(NULL);
		free_t2(_args);
	}
	dup2(stdout_fd, 1);
	dup2(stdin_fd, 0);
	i = 0;
	free(env);
	free(path);
	free_t2(args);
	return ;
}
