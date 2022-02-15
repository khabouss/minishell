/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pip.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majdahim <majdahim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 02:22:56 by majdahim          #+#    #+#             */
/*   Updated: 2022/02/14 03:29:06 by majdahim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	**ft_pipe(int pips)
{
	int		**pipe_fd;
	int		i;

	pipe_fd = (int **)malloc(pips * sizeof(int *));
	i = -1;
	while (++i < pips)
	{
		pipe_fd[i] = (int *)malloc(2 * sizeof(int));
		pipe(pipe_fd[i]);
	}
	return (pipe_fd);
}

void	handle_pipe(char **str_pips, t_list *env_list, int pips)
{
	int		**pipe_fd;
	int		status;
	int		i;

	pipe_fd = ft_pipe(pips);
	i = -1;
	while (++i < pips + 1)
	{
		if (fork() == 0)
		{
			ft_close(i, pips, pipe_fd);
			if (i != 0)
				dup2(pipe_fd[i - 1][0], STDIN_FILENO);
			if (i != pips)
				dup2(pipe_fd[i][1], STDOUT_FILENO);
			ft_execve_pip(str_pips[i], env_list);
			ft_putstr(STDOUT_FILENO, 0);
			ft_close(-1, pips, pipe_fd);
		}
	}
	ft_close(-1, pips, pipe_fd);
	while (wait(&status) > 0)
		;
}
