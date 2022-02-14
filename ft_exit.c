/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majdahim <majdahim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 01:24:39 by majdahim          #+#    #+#             */
/*   Updated: 2022/02/14 02:56:28 by majdahim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exit(int fd, char **args)
{
	if (args[0] && !args[1])
	{
		exit(EXIT_SUCCESS);
	}
	if (args[1])
	{
		if (!ft_isdigit(args[1][0]))
		{
			ft_putstr(fd, "exit\n");
			ft_putstr(fd, "minishell: exit: ");
			ft_putstr(fd, args[1]);
			ft_putstr(fd, ": numeric argument required\n");
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
