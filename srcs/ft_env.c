/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majdahim <majdahim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 01:05:24 by majdahim          #+#    #+#             */
/*   Updated: 2022/02/16 20:58:44 by majdahim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(int fd, t_list *env_list)
{
	t_list	*current;

	current = env_list;
	while (current != NULL)
	{
		ft_putstr(fd, current->env_key);
		ft_putstr(fd, "=");
		ft_putstr(fd, current->env_value);
		ft_putstr(fd, "\n");
		current = current->next;
	}
}

t_list	*fill_env01(t_list *temp, char **env, int i)
{
	char		**s;

	s = ft_split(env[i], '=');
	temp = malloc(sizeof(*temp));
	temp->env = env[i];
	temp->env_key = s[0];
	temp->env_value = s[1];
	temp->next = NULL;
	free(s);
	return (temp);
}

t_list	*fill_env(char **env)
{
	t_list		*head;
	t_list		*tail;
	t_list		*temp;
	int			i;

	head = NULL;
	tail = NULL;
	temp = NULL;
	i = 0;
	while (env[i])
	{
		temp = fill_env01(temp, env, i);
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
