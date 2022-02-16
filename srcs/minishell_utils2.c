/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majdahim <majdahim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 19:53:16 by tkhabous          #+#    #+#             */
/*   Updated: 2022/02/14 13:27:43 by majdahim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_start(char *str, int i)
{
	int		j;

	j = i;
	while (j)
	{
		if (str[j] && str[j] == ' ')
			return (j);
		j--;
	}
	return (j);
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
	if (i)
		free(old);
	return (new);
}

void	ft_free2d(int **arr, int i)
{
	while (i--)
		free(arr[i]);
	free(arr);
}

void	ft_putnbr(int fd, int n)
{
	unsigned int	nb;

	if (n < 0)
	{
		ft_putchar(fd, '-');
		n = -n;
	}
	nb = n;
	if (nb > 9)
	{
		ft_putnbr(fd, nb / 10);
		ft_putchar(fd, (nb % 10) + '0');
	}
	else
		ft_putchar(fd, nb + '0');
}

void	free_t2(char **w)
{
	int		i;
	int		x;

	i = 0;
	x = ft_strlen2(w);
	while (x > i)
	{
		free(w[i]);
		i++;
	}
	free(w);
}
