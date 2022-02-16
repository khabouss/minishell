/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majdahim <majdahim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 02:03:12 by majdahim          #+#    #+#             */
/*   Updated: 2022/02/14 13:32:47 by majdahim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	*replace_dollar(char *s, char *v, int start, int end)
{
	char	*s1;
	char	*s2;
	char	*w, *t;

	w = NULL;
	s1 = ft_substr(s, 0, start - 1);
	s2 = ft_substr(s, end, ft_strlen(s) - end);
	t = ft_strjoin(s1, v);
	w = ft_strjoin(t, s2);
	free(v);
	free(s);
	free(s1);
	free(s2);
	free(t);
	return (w);
}

char	*handling_dollar(char *s, t_list *env_list)
{
	int		i;
	int		start;
	char	*v;
	t_list	*current;
	char	*tmp;

	i = 0;
	start = 0;
	while (s[i])
	{
		if (s[i] == '$')
		{
			start = ++i;
			while (s[i] && s[i] != ' ' && s[i] != '\'' && s[i] != '\"')
				i++;
			v = ft_substr(s, start, i - start);
			current = env_list;
			while (current != NULL && v[0] != '?')
			{
				if (!ft_strcmp(current->env_key, v))
				{
					tmp = ft_substr(s, i, ft_strlen(s));
					s = ft_substr(s, 0, start - 1);
					s = ft_strjoin(s, current->env_value);
					s = ft_strjoin(s, tmp);
					break ;
				}
				current = current->next;
			}
			if (v[0] == '?' && v[1] == '\0')
			{
				char *sigc = ft_itoa(g_sig[1]);
				return (replace_dollar(v, sigc, start, i));
			}
		}
		i++;
	}
	return (s);
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
	args = ft_realloc_2(args, i, (i + 1));
	args[i] = NULL;
	return (args);
}
