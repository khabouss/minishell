/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majdahim <majdahim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 01:19:42 by majdahim          #+#    #+#             */
/*   Updated: 2022/02/14 13:17:56 by majdahim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_list(int fd, t_list *env_list)
{
	t_list	*current;

	current = env_list;
	while (current != NULL)
	{
		ft_putstr(fd, "declare -x ");
		ft_putstr(fd, current->env_key);
		ft_putstr(fd, "=\"");
		ft_putstr(fd, current->env_value);
		ft_putstr(fd, "\"\n");
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
	int		eq_index;
	int		b;

	eq_index = 0;
	s = (char **)malloc(2 * sizeof(char **));
	current = env_list;
	while (args[eq_index] != '=')
		eq_index++;
	s[0] = ft_substr(args, 0, eq_index);
	s[1] = ft_substr(args, eq_index + 1, ft_strlen(args));
	b = 0;
	while (current != NULL)
	{
		if (ft_strcmp(current->env_key, s[0]) == 0)
		{
			current->env_value = s[1];
			b = 1;
			break ;
		}
		current = current->next;
	}
	if (!b)
		ft_lstadd_back(&env_list, add_content(s));
}

void	ft_export(int fd, char **args, t_list *env_list)
{
	int		i;
	int		ret;
	char	**s;
	int		i_key;
	int		a;

	a = 0;
	i_key = 0;
	i = 0;
	if (args)
	{
		while (args[++i])
		{
			a = 0;
			while (args[i][a] != '\0')
			{
				if (args[i][a] == '=')
				{
					s = ft_split(args[i], '=');
					if (!s)
						break ;
					while (s[0][i_key])
					{
						if (!ft_isalpha(s[0][i_key]) && s[0][i_key] != '_'
								&& !ft_isdigit(s[0][i_key]))
							return ;
						i_key++;
					}
					if (!ft_isalpha(s[0][0]) && s[0][0] != '_')
					{
						ft_putstr(1, "export: not an identifier: ");
						ft_putstr(1, s[0]);
						ft_putstr(1, "\n");
						return ;
					}
					else
						addto_list(args[i], env_list);
				}
				a++;
			}
		}
	}
	if (!args[1])
		print_list(fd, env_list);
	else
	{
		a = 0;
		while (args[1][a] != '\0')
		{
			if (args[1][a] == '=')
				return ;
			a++;
		}
		print_list(fd, env_list);
	}
	return ;
}
