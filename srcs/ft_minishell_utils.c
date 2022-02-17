/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majdahim <majdahim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 01:13:23 by majdahim          #+#    #+#             */
/*   Updated: 2022/02/17 01:14:13 by majdahim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*fnorm0(char *str, int start, int i)
{
	char	*ret;

	ret = ft_substr(str, start, (i - start)
			+ (str[(i) + 1] == '\0'));
	return (ret);
}
