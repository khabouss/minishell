/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majdahim <majdahim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 02:10:34 by majdahim          #+#    #+#             */
/*   Updated: 2022/02/16 19:13:30 by majdahim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	delet_v_env1(t_list	*current, t_list *prev, char **s, t_list *temp)
{
	while (current != NULL)
	{
		if (ft_strcmp(current->env_key, s[0]) == 0)
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

void	delet_v_env(t_list *env_list, char *argv)
{
	t_list	*current;
	t_list	*temp;
	t_list	*prev;
	char	**s;

	temp = NULL;
	prev = NULL;
	current = env_list;
	s = ft_split(argv, '=');
	if ((ft_strcmp(current->env_key, s[0]) == 0) && current != NULL)
	{
		temp = current->next;
		free(current);
		current = NULL;
		env_list = temp;
		write(1, "--\n", 3);
		return ;
	}
	delet_v_env1(current, prev, s, temp);
}

void	ft_unset(char **args, t_list *env_list)
{
	int		i;

	i = -1;
	if (args)
		while (args[++i])
			delet_v_env(env_list, args[i]);
}
