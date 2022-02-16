/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majdahim <majdahim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 02:18:20 by majdahim          #+#    #+#             */
/*   Updated: 2022/02/16 04:12:53 by majdahim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_int1(int sig_num)
{
	(void)sig_num;
	if (g_sig[0] == 2)
	{
		ft_putstr(2, "Quit: 3\n");
		g_sig[1] = 131;
	}
	else
	{
		rl_on_new_line();
		rl_redisplay();
	}
}

void	handle_int(int sig_num)
{
	(void)sig_num;
	if (g_sig[0] != 2)
		rl_on_new_line();
	ft_putstr(1, "\n");
	rl_replace_line("", 0);
	rl_redisplay();
	g_sig[1] = 1;
}
