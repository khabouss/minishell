/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majdahim <majdahim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 15:19:26 by majdahim          #+#    #+#             */
/*   Updated: 2022/01/07 15:23:15 by majdahim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*replace_dollar(char *s, char *v, int start, int end)
{
	char	*s1;
	char	*s2;
	char	*w;

	w = NULL;
	s1 = ft_substr(s, 0, start - 1);
	s2 = ft_substr(s, end, ft_strlen(s) - end);
	w = ft_strjoin(s1, v);
	w = ft_strjoin(w, s2);
	return (w);
}

char	*handling_dollar(char *s, t_list *env_list)
{
	int		i;
	int		start;
	char	*v;
	t_list	*current;

	i = 0;
	start = 0;
	current = env_list;
	while (s[i])
	{
		if (s[i] == '$')
		{
			start = ++i;
			while (s[i] && s[i] != ' ')
				i++;
			v = ft_substr(s, start, i - start);
			while (current != NULL)
			{
				if (!ft_strcmp(current->env_key, v))
					return (replace_dollar(s, current->env_value, start, i));
				current = current->next;
			}
		}
		i++;
	}
	return (s);
}

int	search_second_quote(char *s, int start, char type)
{
	if (type == '\'')
	{
		while (s[start])
		{
			if (s[start] == type)
				return (start);
			start++;
		}
		return (0);
	}
	else if (type == '\"')
	{
		while (s[start])
		{
			if (s[start] == type && s[start] != '\\')
				return (start);
			start++;
		}
		return (0);
	}
	return (0);
}

char	**get_args(char *s, t_list *env_list)
{
	int		i;
	int		end;
	int		start;
	char	**args;

	start = 0;
	end = 0;
	i = 0;
	while (s[start])
	{
		if (s[start] == '\'' || s[start] == '\"')
		{
			if (s[start - 1] == '\\')
				continue ;
			end = search_second_quote(s, start + 1, s[start]);
			if (!end)
				printf("error multiligne\n");
			args = ft_realloc_2(args, i, (i + 1));
			if (s[start] != '\'' && s[start] != '\"')
				args[i] = ft_substr(s, start, end - start);
			else
				args[i] = ft_substr(s, start + 1, end - start - 1);
			if (s[start] == '\"' && s[end] == '\"')
				args[i] = handling_dollar(args[i], env_list);
			i++;
			start = end + 1;
		}
		else
		{
			end = start;
			while (s[end] && s[end] != ' ')
				end++;
			if (end > start)
			{
				args = ft_realloc_2(args, i, (i + 1));
				if (s[start] != '\'' && s[start] != '\"')
					args[i] = ft_substr(s, start, end - start);
				else
					args[i] = ft_substr(s, start + 1, end - start - 1);
				args[i] = handling_dollar(args[i], env_list);
				i++;
			}
			start = end;
		}
		while (s[start] && s[start] == ' ')
			start++;
	}
	return (args);
}
