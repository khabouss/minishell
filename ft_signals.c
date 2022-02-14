/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majdahim <majdahim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 02:18:20 by majdahim          #+#    #+#             */
/*   Updated: 2022/02/14 13:19:06 by majdahim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_int1(int sig_num)
{
	if (g_sig == 2)
		ft_putstr(1, "Quit: 3\n");
}

void	handle_int(int sig_num)
{
	rl_on_new_line();
	ft_putstr(1, "\n");
	rl_replace_line("", 0);
	rl_redisplay();
}
