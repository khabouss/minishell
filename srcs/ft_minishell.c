/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majdahim <majdahim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 02:16:41 by majdahim          #+#    #+#             */
/*   Updated: 2022/02/15 18:40:09 by majdahim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	(void)argv;
	(void)argc;
	char	*str;
	char	**args;
	int		start;
	t_list	*env_list;
	int		pips;
	int		i;
	int		return_value;
	char	*tmp;

	return_value = 0;
	args = NULL;
	tmp = NULL;
	env_list = fill_env(env);
	signal(SIGQUIT, handle_int1);
	signal(SIGINT, handle_int);
	while (1)
	{
		g_sig[0] = 0;
		str = readline(PROMPT);
		str = ft_strtrim(str, " ");
		if (str == NULL)
			exit(0);
		pips = 0;
		i = 0;
		add_history(str);
		start = 0;
		while (str[i] != '\0')
		{
			if (str[i] != '\0' && str[i + 1] != '\0' && str[i] == '$' && str[i + 1] == '?')
			{
				tmp = ft_substr(str, i + 2, ft_strlen(str));
				str = ft_substr(str, 0, i);
				str = ft_strjoin(str, ft_itoa(g_sig[1]));
				str = ft_strjoin(str, tmp);
			}
			i++;
		}
		i = 0;
		if (tmp != NULL)
			free(tmp);
		tmp = NULL;
		while (str[i] != '\0')
		{
			if (str[i] == '\'' || str[i] == '\"')
			{
				++i;
				while (str[i] != '\0' && str[i] != '\'' && str[i] != '\"')
				{
					i++;
				}
				i++;
			}
			if (str[i] == '|' || str[i + 1] == '\0')
			{
				args = ft_realloc_2(args, pips, pips + 1);
				tmp = ft_substr(str, start, (i - start) + (str[i + 1] == '\0'));
				args[pips] = tmp;
				start = i + 1;
				if (str[i] == '|')
					pips++;
			}
			i++;
		}
		
		if (pips)
		{
			handle_pipe(args, env_list, pips);
		}
		else
		{
			if (args != NULL && str[0] != '\0')
				ft_execve_non_pip(args[0], env_list, env);
		}
		//system("leaks minishell");
	}
	return (0);
}
