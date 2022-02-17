/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majdahim <majdahim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 02:16:41 by majdahim          #+#    #+#             */
/*   Updated: 2022/02/17 01:13:31 by majdahim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pip_with_non(char **args, char *str, int pips, t_list *env_list)
{
	int		i;
	char	**env;

	env = NULL;
	if (pips)
	{
		handle_pipe(args, env_list, pips);
		i = 0;
		while (i < pips)
			free(args[i++]);
		free(args);
	}
	else
	{
		if (args != NULL && str[0] != '\0')
			ft_execve_non_pip(args[0], env_list, env);
		free(args[0]);
		free(args);
	}
}

char	*check_dollar_rep(char *str)
{
	int		i;
	char	*tmp;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] != '\0' && str[i + 1] != '\0'
			&& str[i] == '$' && str[i + 1] == '?')
		{
			tmp = ft_substr(str, i + 2, ft_strlen(str));
			str = ft_substr(str, 0, i);
			str = ft_strjoin(str, ft_itoa(g_sig[1]));
			str = ft_strjoin(str, tmp);
			free(tmp);
			tmp = NULL;
		}
		i++;
	}
	return (str);
}

void	check_pips(char *str, char **args, int start, t_list *env_list)
{
	int		i[2];
	char	*tmp;

	i[0] = -1;
	i[1] = 0;
	while (str[++i[0]] != '\0')
	{
		if (str[i[0]] == '\'' || str[i[0]] == '\"')
		{
			++i[0];
			while (str[i[0]] != '\0' && str[i[0]] != '\'' && str[i[0]] != '\"')
				i[0]++;
			i[0]++;
		}
		if (str[i[0]] == '|' || str[i[0] + 1] == '\0')
		{
			args = ft_realloc_2(args, i[1], i[1] + 1);
			tmp = fnorm0(str, start, i[0]);
			args[i[1]] = tmp;
			start = i[0] + 1;
			if (str[i[0]] == '|')
				i[1]++;
		}
	}
	pip_with_non(args, str, i[1], env_list);
}

void	init(int ac, char **av)
{
	(void)ac;
	(void)av;
}

int	main(int argc, char **argv, char **env)
{
	char	*str;
	char	*str_raw;
	char	**args;
	t_list	*env_list;

	args = NULL;
	init(argc, argv);
	env_list = fill_env(env);
	signal(SIGQUIT, handle_int1);
	signal(SIGINT, handle_int);
	while (1)
	{
		g_sig[0] = 0;
		str_raw = readline(PROMPT);
		str = ft_strtrim(str_raw, " ");
		free(str_raw);
		if (str == NULL)
			exit(0);
		add_history(str);
		str = check_dollar_rep(str);
		check_pips(str, args, 0, env_list);
		free(str);
	}
	return (0);
}
