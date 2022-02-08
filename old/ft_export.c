/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majdahim <majdahim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 15:59:39 by majdahim          #+#    #+#             */
/*   Updated: 2022/01/07 16:11:18 by majdahim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_list(int fd, t_list *env_list)
{
	t_list		*current;

	current = env_list;
	while (current != NULL)
	{
		ft_putstr(fd, "declare -x ");
		ft_putstr(fd, current->env_key);
		if (current->env_value)
		{
			ft_putstr(fd, "=\"");
			ft_putstr(fd, current->env_value);
			ft_putstr(fd, "\"\n");
		}
		else
			ft_putstr(fd, "\n");
		current = current->next;
	}
}

t_list	*add_content(char **content)
{
	t_list	*lst;

	lst = malloc(sizeof(t_list));
	if (!lst)
		return (NULL);
	lst->env_key = content[0];
	lst->env_value = content[1];
	lst->next = NULL;
	return (lst);
}

void	ft_lstadd_back(t_list **env_list, t_list *new)
{
	t_list	*begin;

	if (env_list && (*env_list) && new)
	{
		begin = (*env_list);
		if (begin == NULL)
			(*env_list) = new;
		else
		{
			while (begin->next)
				begin = begin->next;
			begin->next = new;
		}
	}
}

void	addto_list(char *args, t_list *env_list)
{
	t_list	*current;
	char	**s;
	int		b;

	current = env_list;
	s = ft_split(args, '=');
	b = 0;
	while (current != NULL)
	{
		if (ft_strcmp(current->env_key, s[0]) == 0)
		{
			if (s[1])
				current->env_value = s[1];
			b = 1;
			break ;
		}
		current = current->next;
	}
	if (!b)
		ft_lstadd_back(&env_list, add_content(s));
}

int	ft_export(int fd, char **args, t_list *env_list)
{
	int		i;
	int		ret;
	char	**s;
	int		i_key;

	i_key = 0;
	i = 0;
	if (args)
	{
		while (args[++i])
		{
			s = ft_split(args[i], '=');
			while (s[0][i_key])
			{
				if (!ft_isalpha(s[0][i_key]) && s[0][i_key] != '_'
						&& !ft_isdigit(s[0][i_key]))
					return (1);
				i_key++;
			}
			if (!ft_isalpha(s[0][0]) && s[0][0] != '_')
			{
				ft_putstr(1, "export: not an identifier: ");
				ft_putstr(1, s[0]);
				ft_putstr(1, "\n");
				return (1);
			}
			else
				addto_list(args[i], env_list);
		}	
	}
	if (!args[1])
		print_list(fd, env_list);
	return (0);
}
