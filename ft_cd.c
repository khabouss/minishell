/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majdahim <majdahim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 01:06:37 by majdahim          #+#    #+#             */
/*   Updated: 2022/02/14 13:09:53 by majdahim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	searchch(char *word, char *changed, t_list *env_list)
{
	t_list	*current;

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

char	*get_home_incd(t_list *env_list)
{
	t_list	*current;
	char	*home;

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

void	ft_cd(int fd, char **args, t_list *env_list)
{
	char	*pwd;
	char	*path;
	char	*home;

	path = getcwd(path, 0);
	home = get_home_incd(env_list);
	pwd = NULL;
	if (ft_strcmp(".", args[1]) == 0 || args[1] == NULL)
		args[1] = home;
	if (chdir(args[1]) != 0)
	{
		ft_putstr(1, "Minishell: cd: ");
		ft_putstr(1, args[1]);
		ft_putstr(1, ": Not a directory\n");
	}
	pwd = getcwd(pwd, 0);
	searchch("PWD", pwd, env_list);
	searchch("OLDPWD", path, env_list);
}
