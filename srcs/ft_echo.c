/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majdahim <majdahim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 01:01:10 by majdahim          #+#    #+#             */
/*   Updated: 2022/02/16 03:38:02 by majdahim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include "minishell.h"

void	ft_echo1(int argc, int sp, char **args, int i)
{
	while (i < argc)
	{
		ft_putstr(STDOUT_FILENO, args[i]);
		i++;
		if (args[i] && args[i][0] != '\0')
			ft_putstr(STDOUT_FILENO, " ");
	}
	if (sp == 0)
		ft_putstr(STDOUT_FILENO, "\n");
}

void	ft_echo(char **args)
{
	int		i;
	int		j;
	int		argc;
	int		sp;

	j = 1;
	sp = 0;
	argc = ft_strlen2(args);
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
			break ;
	}
	ft_echo1(argc, sp, args, i);
}
