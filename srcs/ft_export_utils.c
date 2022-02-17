/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majdahim <majdahim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 18:57:09 by majdahim          #+#    #+#             */
/*   Updated: 2022/02/17 01:24:10 by majdahim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	export_invalid(char *args)
{
	ft_putstr(2, "Minishell: export: `");
	ft_putstr(2, args);
	ft_putstr(2, "\': not a valid identifier\n");
	g_sig[1] = 1;
}

void	check_first_char(char **s)
{
	int		i_key;

	i_key = 0;
	while (s[0][i_key])
	{
		if (!ft_isalpha(s[0][i_key]) && s[0][i_key] != '_'
				&& !ft_isdigit(s[0][i_key]))
		{
			return ;
		}
		i_key++;
	}
	if (!ft_isalpha(s[0][0]) && s[0][0] != '_')
	{
		ft_putstr(2, "Minishell: export: `");
		ft_putstr(2, s[0]);
		ft_putstr(2, "\': not a valid identifier\n");
		g_sig[1] = 1;
		return ;
	}
}

int	check_export(char **args, int i, int isvalid, t_list *env_list)
{
	int		a;
	char	**s;

	a = 0;
	while (args[i][a] != '\0')
	{
		if (args[i][a] == '=')
		{
			s = ft_split(args[i], '=');
			if (!s)
				break ;
			if (!ft_isalpha(s[0][0]) && s[0][0] != '_')
				check_first_char(s);
			else
			{
				isvalid = 1;
				addto_list(args[i], env_list);
			}
		}
		a++;
	}
	return (isvalid);
}
