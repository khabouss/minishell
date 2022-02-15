/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majdahim <majdahim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 01:01:10 by majdahim          #+#    #+#             */
/*   Updated: 2022/02/14 13:34:09 by majdahim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(int fd, char **args)
{
	int		i;
	int		j;
	int		check_n;
	int		argc;
	int		sp;

	j = 1;
	sp = 0;
	argc = ft_strlen2(args);
	check_n = 0;
	i = 1;
	while (args[i] && args[i][0] == '-')
	{
		while (args[i][j] == 'n')
			j++;
		if (args[i][j] == '\0')
		{
			sp = 1;
			i++;
		}
		else
			break;
	}
	while (i < argc)
	{
		ft_putstr(fd, args[i]);
		i++;
		if (args[i] && args[i][0] != '\0')
			ft_putstr(fd, " ");
	}
	if (sp == 0)
		ft_putstr(fd, "\n");
}
