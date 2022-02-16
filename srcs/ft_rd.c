/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majdahim <majdahim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 02:13:46 by majdahim          #+#    #+#             */
/*   Updated: 2022/02/15 18:18:45 by majdahim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_heredoc(char **args, int i, int old)
{
	char	*eof;
	char	*input;
	char	*buff;
	int		fd;
	int		old_stdin;

	if (old != -1)
		dup2(old, 0);
	if (args[i][2] != '\0')
		eof = ft_substr(args[i], 2, ft_strlen(args[i]) - 2);
	else
	{
		eof = ft_strdup(args[i + 1]);
		args[i + 1][0] = '\0';
	}
	input = NULL;
	buff = "";
	fd = open("heredoc_temp", O_CREAT | O_RDWR | O_TRUNC, 0666);
	while (ft_strcmp(input, eof) != 0)
	{
		input = readline("> ");
		if (ft_strcmp(input, eof) != 0)
		{
			buff = ft_strjoin(buff, input);
			buff = ft_strjoin(buff, "\n");
		}
	}
	write(fd, buff, ft_strlen(buff) - 1);
	if (ft_strlen(buff) > 1)
		write(fd, "\n", 1);
	close(fd);
	args[i][0] = '\0';
	fd = open("heredoc_temp", O_RDWR, 0666);
	old_stdin = dup(STDIN_FILENO);
	dup2(fd, STDIN_FILENO);
	return (old_stdin);
}

int	update_out(char **args)
{
	int		i;
	char	*file_name;
	int		fd;
	int		is_double;
	int		in;
	int		old_stdin;
	int		len;

	char *str;
	in = -1;
	i = 0;
	old_stdin = -1;
	len = 0;
	while ((str = args[len]) != NULL)
		len++;
	while (i < len && args[i])
	{
		is_double = 0;
		if (args[i][0] == '>')
		{
			in = 0;
			if (args[i][1] == '>')
				is_double = 1;
			if (args[i][1 + is_double] != '\0')
				file_name = ft_substr(args[i], 1 + is_double,
						ft_strlen(args[i]) - 1 - is_double);
			else
			{
				file_name = ft_strdup(args[i + 1]);
				args[i + 1][0] = '\0';
			}
			if (is_double == 0)
				fd = open(file_name, O_CREAT | O_RDWR | O_TRUNC, 0666);
			else
				fd = open(file_name, O_CREAT | O_RDWR | O_APPEND, 0666);
			free(file_name);
			args[i][0] = '\0';
		}
		if (args[i][0] == '<' && args[i][1] != '<')
		{
			in = 1;
			if (args[i][1] != '\0')
				file_name = ft_substr(args[i], 1, ft_strlen(args[i]) - 1);
			else
			{
				file_name = ft_strdup(args[i + 1]);
				args[i + 1][0] = '\0';
			}
			fd = open(file_name, O_RDWR, 0666);
			if (fd == -1)
			{
				ft_putstr(2, "Minishell: ");
				ft_putstr(2, file_name);
				ft_putstr(2, ": No such file or directory\n");
				g_sig[1] = 1;
				free(file_name);
				return (-1);
			}
			args[i][0] = '\0';
		}
		if (args[i][0] == '<' && args[i][1] == '<')
			old_stdin = ft_heredoc(args, i, old_stdin);
		i++;
	}
	if (in == 0)
	{
		dup2(fd, STDOUT_FILENO);
		return (fd);
	}
	if (in == 1)
	{
		dup2(fd, STDIN_FILENO);
		return (fd);
	}
	return (0);
}
