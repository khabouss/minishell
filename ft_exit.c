/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majdahim <majdahim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 16:24:58 by majdahim          #+#    #+#             */
/*   Updated: 2022/01/07 16:29:28 by majdahim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exit(int fd, char **args)
{
	if (args[0] && !args[1])
	{
		exit(0);
	}
	if (args[1])
	{
		if (!ft_isdigit(args[1][0]))
		{
			ft_putstr(fd, "exit\n");
			ft_putstr(fd, "minishell: exit: ");
			ft_putstr(fd, args[1]);
			ft_putstr(fd, ": numeric argument required");
			exit(255);
		}
	}
	if (args[2])
	{
		ft_putstr(fd, "exit\n");
		ft_putstr(fd, "minishell: exit: too many arguments\n");
		return (1);
	}
	else
	{
		exit(ft_atoi(args[1]) % 256);
	}
	return (0);
}
