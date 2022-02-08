/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majdahim <majdahim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 15:16:37 by majdahim          #+#    #+#             */
/*   Updated: 2022/01/07 15:34:08 by majdahim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1)
		return (s2[i]);
	else if (!s2)
		return (s1[i]);
	while (s1[i] && s2[i] && s1[i] == s2[i])
	{
		i++;
	}
	return (s1[i] - s2[i]);
}

char	**ft_realloc_2(char **old, size_t old_size, size_t new_size)
{
	char	**new;
	int		i;

	new = malloc(sizeof(char *) * (new_size + 1));
	i = 0;
	while (i < (int)old_size)
	{
		new[i] = old[i];
		i++;
	}
	return (new);
}

void	ft_putchar(int fd, char c)
{
	write(fd, &c, 1);
}

void	ft_putstr(int fd, char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		ft_putchar(fd, s[i]);
		i++;
	}
}

int	ft_strlen2(char **w)
{
	int	i;

	i = 0;
	while (w[i])
		i++;
	return (i);
}
