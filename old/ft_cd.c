/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majdahim <majdahim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 15:39:29 by majdahim          #+#    #+#             */
/*   Updated: 2022/01/07 16:12:15 by majdahim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_home_incd(t_list *env_list)
{
	t_list		*current;
	char		*home;

	current = env_list;
	while (current != NULL)
	{
		if (ft_strcmp(current->env_key, "HOME") == 0)
		{
			home = current->env_value;
			break ;
		}
		current = current->next;
	}
	return (home);
}

void	searchch(char *word, char *changed, t_list *env_list)
{
	t_list		*current;

	current = env_list;
	while (current != NULL)
	{
		if (ft_strcmp(current->env_key, word) == 0)
		{
			current->env_value = changed;
			break ;
		}
		current = current->next;
	}
}

void	ft_cd(int fd, char **args, t_list *env_list)
{
	char	*pwd;
	char	*path;
	char	*home;

	path = NULL;
	path = getcwd(path, 0);
	home = get_home_incd(env_list);
	pwd = NULL;
	if (!args[1])
		args[1] = home;
	if (chdir(args[1]) != 0)
		ft_putstr(1, "Error\n");
	pwd = getcwd(pwd, 0);
	searchch("PWD", pwd, env_list);
	searchch("OLDPWD", path, env_list);
}
