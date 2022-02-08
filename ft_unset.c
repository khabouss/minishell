/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majdahim <majdahim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 16:13:37 by majdahim          #+#    #+#             */
/*   Updated: 2022/01/07 16:23:34 by majdahim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	delet_v_env(t_list *env_list, char *argv)
{
	t_list		*current;
	t_list		*temp;
	t_list		*prev;
	char		**s;

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

int	ft_unset(char **args, t_list *env_list)
{
	int		i;
	char	**s;
	int		i_key;

	i = -1;
	if (args)
		while (args[++i])
		{
			s = ft_split(args[i], '=');
			if (!ft_isalpha(s[0][0]) && s[0][0] != '_')
				return (1);
			while (s[0][i_key])
			{
				if (!ft_isalpha(s[0][i_key]) && s[0][i_key] != '_'
						&& !ft_isdigit(s[0][i_key]))
					return (1);
				i_key++;
			}
			delet_v_env(env_list, args[i]);
		}
	return (0);
}
