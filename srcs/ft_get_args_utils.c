/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_args_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majdahim <majdahim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 23:44:20 by majdahim          #+#    #+#             */
/*   Updated: 2022/02/16 23:46:18 by majdahim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*fun1(int start, int end, char *s, t_list *env_list)
{
	char	*str;

	if (!end)
		printf("error multiligne\n");
	if (s[start] != '\'' && s[start] != '\"')
		str = ft_substr(s, start, end - start);
	else
		str = ft_substr(s, start + 1, end - start - 1);
	if (s[start] == '\"' && s[end] == '\"')
		str = handling_dollar(str, env_list);
	return (str);
}

int	get_end(int start, int end, char *s)
{
	end = start;
	while (s[end] && s[end] != ' ')
		end++;
	return (end);
}

int	update_start(char *s, int start)
{
	while (s[start] && s[start] == ' ')
			start++;
	return (start);
}

char	**args_getter(int *data, char **args, char *s, t_list *env_list)
{
	while (s[data[0]])
	{
		if (s[data[0]] == '\'' || s[data[0]] == '\"')
		{
			data[1] = search_second_quote(s, data[0] + 1, s[data[0]]);
			args = ft_realloc_2(args, data[2], (data[2] + 1));
			args[data[2]++] = fun1(data[0], data[1], s, env_list);
			data[0] = data[1] + 1;
		}
		else
		{
			data[1] = get_end(data[0], data[1], s);
			if (data[1] > data[0])
			{
				args = ft_realloc_2(args, data[2], (data[2] + 1));
				args[data[2]] = fun1(data[0], data[1], s, env_list);
				args[data[2]] = handling_dollar(args[data[2]], env_list);
				data[2]++;
			}
			data[0] = data[1];
		}
		data[0] = update_start(s, data[0]);
	}
	args = ft_realloc_2(args, data[2], (data[2] + 1));
	return (args);
}
