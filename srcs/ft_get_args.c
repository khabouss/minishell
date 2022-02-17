/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majdahim <majdahim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 02:03:12 by majdahim          #+#    #+#             */
/*   Updated: 2022/02/16 23:44:50 by majdahim         ###   ########.fr       */
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
	char	*w;
	char	*t;

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

char	*handling_dollar1(char *s, int i, int start, t_list *env_list)
{
	t_list	*current;
	char	*tmp;
	char	*v;

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
		return (replace_dollar(v, ft_itoa(g_sig[1]), start, i));
	return (s);
}

char	*handling_dollar(char *s, t_list *env_list)
{
	int		i;
	int		start;

	i = 0;
	start = 0;
	while (s[i])
	{
		if (s[i] == '$')
		{
			start = ++i;
			while (s[i] && s[i] != ' ' && s[i] != '\'' && s[i] != '\"')
				i++;
			s = handling_dollar1(s, i, start, env_list);
		}
		i++;
	}
	return (s);
}

char	**get_args(char *s, t_list *env_list)
{
	char	**args;
	int		data[3];

	args = NULL;
	data[0] = 0;
	data[1] = 0;
	data[2] = 0;
	args = args_getter(data, args, s, env_list);
	return (args);
}
