/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majdahim <majdahim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 02:09:36 by majdahim          #+#    #+#             */
/*   Updated: 2022/02/16 19:36:36 by majdahim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_path(char **w, int fd, char **args)
{
	char	*s;
	int		i;

	i = 0;
	s = NULL;
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
	return (NULL);
}

char	*check_fill_path(t_list *env_list, char **args)
{
	char	**w;
	int		fd;
	char	*s;
	t_list	*current;

	fd = 0;
	s = NULL;
	current = env_list;
	while (current != NULL)
	{
		if (!ft_strcmp(current->env_key, "PATH"))
		{
			w = ft_split(current->env_value, ':');
			s = get_path(w, fd, args);
			if (s != NULL)
				return (s);
		}
		current = current->next;
	}
	return (0);
}
