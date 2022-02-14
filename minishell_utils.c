/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majdahim <majdahim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 13:28:12 by yer-raki          #+#    #+#             */
/*   Updated: 2022/02/14 13:24:25 by majdahim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	int		i;

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

int	ft_strlen2(char **w)
{
	int		i;

	i = 0;
	while (w[i])
		i++;
	return (i);
}

void	ft_putchar(int fd, char c)
{
	write(fd, &c, 1);
}

void	*ft_realloc(void *ptr, size_t old_size, size_t new_size)
{
	void	*new;

	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}
	new = malloc(new_size * sizeof(char));
	if (!new)
		return (NULL);
	if (ptr != NULL || !old_size)
	{
		if (old_size >= new_size)
			ft_memcpy(new, ptr, new_size);
		else
			ft_memcpy(new, ptr, old_size);
		free(ptr);
	}
	return (new);
}

char	*ft_strcpy(char *dest, char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
