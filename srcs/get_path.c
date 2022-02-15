/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majdahim <majdahim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 02:09:36 by majdahim          #+#    #+#             */
/*   Updated: 2022/02/14 02:58:27 by majdahim         ###   ########.fr       */
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
