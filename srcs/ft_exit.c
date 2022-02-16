/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majdahim <majdahim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 01:24:39 by majdahim          #+#    #+#             */
/*   Updated: 2022/02/16 04:02:35 by majdahim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_exit(char **args)
{
	ft_putstr(2, "exit\n");
	ft_putstr(2, "minishell: exit: ");
	ft_putstr(2, args[1]);
	ft_putstr(2, ": numeric argument required\n");
	g_sig[1] = 255;
	exit(255);
}

void	ft_exit(int fd, char **args)
{
	(void)fd;
	if (args[0] && !args[1])
	{
		g_sig[1] = 0;
		exit(g_sig[1]);
	}
	if (args[1])
	{
		if (!ft_isdigit(args[1][0]))
		{
			check_exit(args);
		}
	}
	if (args[2])
	{
		ft_putstr(2, "exit\n");
		ft_putstr(2, "minishell: exit: too many arguments\n");
		g_sig[1] = 1;
		return ;
	}
	else
	{
		exit(ft_atoi(args[1]) % 256);
	}
}
