/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majdahim <majdahim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 02:16:41 by majdahim          #+#    #+#             */
/*   Updated: 2022/02/14 03:10:13 by majdahim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	char	*str;
	char	**str_pip;
	t_list	*env_list;
	pid_t	pid;
	int		pips;
	int		i;
	int		status;

	env_list = fill_env(env);
	signal(SIGQUIT, handle_int1);
	signal(SIGINT, handle_int);
	while (1)
	{
		str = readline(PROMPT);
		if (str == NULL)
			exit(0);
		pips = 0;
		i = 0;
		add_history(str);
		while (str[i] != '\0')
		{
			if (str[i] == '\'' || str[i] == '\"')
			{
				++i;
				while (str[i] != '\0')
				{
					if (str[i] == '\'' || str[i] == '\"')
						break ;
					i++;
				}
			}
			if (str[i] == '|')
				pips++;
			i++;
		}
		if (pips)
		{
			str_pip = ft_split(str, '|');
			handle_pipe(str_pip, env_list, pips);
		}
		else
		{
			ft_execve_non_pip(str, env_list, env);
		}
	}
	return (0);
}
