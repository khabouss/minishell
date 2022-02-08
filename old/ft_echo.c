/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majdahim <majdahim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 15:18:32 by majdahim          #+#    #+#             */
/*   Updated: 2022/01/07 15:24:21 by majdahim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo(int fd, char **args, t_list *env_list)
{
	int		i;
	int		check_n;
	int		argc;
	int		sp;

	sp = 0;
	argc = ft_strlen2(args);
	check_n = 0;
	i = 1;
	while (ft_strcmp("-n", args[i]) == 0)
	{
		sp = 1;
		i++;
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
	return (0);
}
