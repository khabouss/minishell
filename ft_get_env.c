/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majdahim <majdahim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 02:12:18 by majdahim          #+#    #+#             */
/*   Updated: 2022/02/14 13:36:09 by majdahim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_env(t_list *env_list)
{
	t_list	*current;
	char	**env;
	int		size;

	size = -1;
	current = env_list;
	while (current != NULL)
	{
		++size;
		env = ft_realloc_2(env, size, size + 1);
		env[size] = current->env;
		current = current->next;
	}
	env = ft_realloc_2(env, size, size + 1);
	env[size] = NULL;
	return (env);
}
