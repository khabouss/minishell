/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majdahim <majdahim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 15:35:23 by majdahim          #+#    #+#             */
/*   Updated: 2022/01/07 15:36:15 by majdahim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(int fd, t_list *env_list)
{
	t_list		*current;

	current = env_list;
	while (current != NULL)
	{
		ft_putstr(fd, current->env_key);
		ft_putstr(fd, "=");
		if (current->env_value)
			ft_putstr(fd, current->env_value);
		ft_putstr(fd, "\n");
		current = current->next;
	}
	return (0);
}
