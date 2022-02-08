/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majdahim <majdahim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 16:42:29 by majdahim          #+#    #+#             */
/*   Updated: 2022/01/07 19:06:31 by majdahim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*check_fill_path(t_list *env_list, char **args)
{
	int		i;
	char	**w;
	char	*s;
	int		fd;
	t_list	*current;

	i = 0;
	fd = 0;
	s = NULL;
	current = env_list;
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

void	ft_execve1(t_list *env_list, char **args, char **env)
{
	char		*path;
	pid_t		pid;
	int			status;
	char		*pwd;

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
	if (path == 0)
	{
		printf("command not found \n");
		exit(127);
	}
	// signal(SIGINT, handle_int01);
	if ((pid = fork()) == 0)
	{
		int nn = execve(path, args, env);
		printf("=====>%d === %s=== args== %d\n", nn, path, errno);
		exit(nn);
	}
	waitpid(pid, &status, 0);
}
