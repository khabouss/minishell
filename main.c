/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majdahim <majdahim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 19:53:16 by tkhabous          #+#    #+#             */
/*   Updated: 2022/02/12 20:44:50 by majdahim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int sig;

void ft_echo(int fd, char **args)
{
	int i, j = 1;
	int check_n;
	int argc;
	int sp;

	sp = 0;
	argc = ft_strlen2(args);
	check_n = 0;
	i = 1;
	while (args[i][0] == '-')
	{
		while (args[i][j] == 'n')
			j++;
		if (args[i][j] == '\0')
		{
			sp = 1;
			i++;
		}
	}
	while (i < argc)
	{
		ft_putstr(fd, args[i]);
		i++;
		if (args[i] && args[i][0] != '\0')
			ft_putstr(fd, " ");
	}
	if (sp == 0)
		ft_putstr(fd, "\n");
}

t_list *fill_env(char **env)
{
	t_list *head;
	t_list *tail;
	t_list *temp;
	char **s;
	int i;

	head = NULL;
	tail = NULL;

	i = 0;
	while (env[i])
	{
		s = ft_split(env[i], '=');
		temp = malloc(sizeof(*temp));
		temp->env = env[i];
		temp->env_key = s[0];
		temp->env_value = s[1];
		temp->next = NULL;
		if (!head)
		{
			head = temp;
			tail = head;
		}
		else
		{
			tail->next = temp;
			tail = temp;
		}
		i++;
	}
	return (head);
}

void ft_env(int fd, t_list *env_list)
{
	t_list *current;

	current = env_list;
	while (current != NULL)
	{
		ft_putstr(fd, current->env_key);
		ft_putstr(fd, "=");
		ft_putstr(fd, current->env_value);
		ft_putstr(fd, "\n");
		current = current->next;
	}
}

void ft_pwd(int fd)
{
	char *r;

	r = NULL;
	ft_putstr(fd, getcwd(r, 1));
	ft_putstr(fd, "\n");
}

void searchch(char *word, char *changed, t_list *env_list)
{
	t_list *current;

	current = env_list;
	while (current != NULL)
	{
		if (ft_strcmp(current->env_key, word) == 0)
		{
			current->env_value = changed;
			break;
		}
		current = current->next;
	}
}

char *get_home_incd(t_list *env_list)
{
	t_list *current;
	char *home;

	current = env_list;
	while (current != NULL)
	{
		if (ft_strcmp(current->env_key, "HOME") == 0)
		{
			home = current->env_value;
			break;
		}
		current = current->next;
	}
	return (home);
}

void ft_cd(int fd, char **args, t_list *env_list)
{
	char *pwd;
	char *path;
	char *home;

	path = getcwd(path, 0);
	home = get_home_incd(env_list);
	pwd = NULL;
	if (ft_strcmp(".", args[1]) == 0 || args[1] == NULL)
		args[1] = home;
	if (chdir(args[1]) != 0)
	{
		ft_putstr(1, "Minishell: cd: ");
		ft_putstr(1, args[1]);
		ft_putstr(1, ": Not a directory\n");
	}
	pwd = getcwd(pwd, 0);
	searchch("PWD", pwd, env_list);
	searchch("OLDPWD", path, env_list);
}

void print_list(int fd, t_list *env_list)
{
	t_list *current;

	current = env_list;
	while (current != NULL)
	{
		ft_putstr(fd, "declare -x ");
		ft_putstr(fd, current->env_key);
		ft_putstr(fd, "=\"");
		ft_putstr(fd, current->env_value);
		ft_putstr(fd, "\"\n");
		current = current->next;
	}
}

t_list *add_content(char **content)
{
	t_list *lst;

	if (!(lst = malloc(sizeof(t_list))))
		return (NULL);
	lst->env_key = content[0];
	lst->env_value = content[1];
	lst->next = NULL;
	return (lst);
}

void ft_lstadd_back(t_list **env_list, t_list *new)
{
	t_list *begin;

	if (env_list && (*env_list) && new)
	{
		begin = (*env_list);
		if (begin == NULL)
			(*env_list) = new;
		else
		{
			while (begin->next)
				begin = begin->next;
			begin->next = new;
		}
	}
}

void addto_list(char *args, t_list *env_list)
{
	t_list *current;
	char **s;
	int eq_index = 0;
	int b;

	s = (char **)malloc(2 * sizeof(char **));
	current = env_list;
	while (args[eq_index] != '=')
		eq_index++;
	s[0] = ft_substr(args, 0, eq_index);
	s[1] = ft_substr(args, eq_index + 1, ft_strlen(args));
	b = 0;
	while (current != NULL)
	{
		if (ft_strcmp(current->env_key, s[0]) == 0)
		{
			current->env_value = s[1];
			b = 1;
			break;
		}
		current = current->next;
	}
	if (!b)
		ft_lstadd_back(&env_list, add_content(s));
}

void ft_export(int fd, char **args, t_list *env_list)
{
	// int i;

	// i = 0;
	// if (args)
	// {
	// 	while (args[++i])
	// 		addto_list(args[i], env_list);
	// }
	// if (!args[1])
	// 	print_list(fd, env_list);

	// ====
	int i;
	int ret;
	char **s;
	int i_key;
	int a = 0;

	i_key = 0;
	i = 0;
	if (args)
	{
		while (args[++i])
		{
			a = 0;
			while (args[i][a] != '\0')
			{
				if (args[i][a] == '=')
				{
					s = ft_split(args[i], '=');
					if (!s)
						break;
					while (s[0][i_key])
					{
						if (!ft_isalpha(s[0][i_key]) && s[0][i_key] != '_' && !ft_isdigit(s[0][i_key]))
							return;
						i_key++;
					}
					if (!ft_isalpha(s[0][0]) && s[0][0] != '_')
					{
						ft_putstr(1, "export: not an identifier: ");
						ft_putstr(1, s[0]);
						ft_putstr(1, "\n");
						return;
					}
					else
						addto_list(args[i], env_list);
				}
				a++;
			}
		}
	}
	if (!args[1])
		print_list(fd, env_list);
	else
	{
		int a = 0;
		while (args[1][a] != '\0')
		{
			if (args[1][a] == '=')
				return;
			a++;
		}
		print_list(fd, env_list);
	}
	return;
}

void delet_v_env(t_list *env_list, char *argv)
{
	t_list *current;
	t_list *temp;
	t_list *prev;
	char **s;

	current = env_list;
	s = ft_split(argv, '=');
	if ((ft_strcmp(current->env_key, s[0]) == 0) && current != NULL)
	{
		temp = current->next;
		free(current);
		current = NULL;
		env_list = temp;
		write(1, "--\n", 3);
		return;
	}
	while (current != NULL)
	{
		if (ft_strcmp(current->env_key, s[0]) == 0)
		{
			temp = current->next;
			prev->next = temp;
			free(current);
			break;
		}
		prev = current;
		current = current->next;
	}
}

void ft_unset(char **args, t_list *env_list)
{
	int i;

	i = -1;
	if (args)
		while (args[++i])
			delet_v_env(env_list, args[i]);
}

char *check_fill_path(t_list *env_list, char **args)
{
	int i;
	char **w;
	char *s;
	int fd;
	t_list *current;

	i = 0;
	fd = 0;
	s = NULL;
	current = env_list;
	while (current != NULL)
	{
		if (!ft_strcmp(current->env_key, "PATH"))
		{
			w = ft_split(current->env_value, ':');
			while (w[i])
			{
				s = ft_strjoin(w[i], "/");
				s = ft_strjoin(s, args[0]);
				fd = open(s, O_RDONLY);
				if (fd > 0)
				{
					close(fd);
					return (s);
				}
				close(fd);
				free(s);
				i++;
			}
		}
		current = current->next;
	}
	return (0);
}

char **fill_paramlist(char *path, char **args, int len, int len_filtered)
{
	int i;
	int j;
	char **w;

	i = 0;
	j = 0;
	w = malloc(sizeof(char *) * (len_filtered + 1));
	while (i < len)
	{
		if (args[i][0] != '\0')
		{
			w[j] = ft_strdup(args[i]);
			j++;
		}
		i++;
	}
	w[j] = NULL;
	return (w);
}

int ft_heredoc(char **args, int i, int old)
{
	char *eof;
	char *input;
	char *buff;
	char *temp;
	int fd;
	int old_stdin;

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

int num_of_cmds(char *str)
{
	int i;
	int cmds;

	i = 0;
	cmds = 0;
	while (str[i] != '\0')
	{
		while (str[i] != '\0' && str[i] != ' ' && str[i] != '\"' && str[i] != '\'')
			i++;
		if (str[i] == ' ' || str[i] == '\0')
		{
			if (i != 0)
				cmds++;
			while (str[i] == ' ')
				i++;
		}
		if (str[i] == '\"')
		{
			i++;
			while (str[i] && str[i] != '\"')
				i++;
			if (str[i] == '\0')
				return (-1);
			if (str[i] == '\"')
				i++;
			if (str[i] == '\0')
				cmds++;
		}
		if (str[i] == '\'')
		{
			i++;
			while (str[i] && str[i] != '\'')
				i++;
			if (str[i] == '\0')
				return (-1);
			if (str[i] == '\'')
				i++;
			if (str[i] == '\0')
				cmds++;
		}
	}
	return (cmds);
}

int get_start(char *str, int i)
{
	int j;

	j = i;
	while (j)
	{
		if (str[j] && str[j] == ' ')
			return (j);
		j--;
	}
	return (j);
}

int update_out(char **args)
{
	int i;
	char *file_name;
	int fd;
	int is_double;
	int in;
	int old_stdin;

	in = -1;
	i = 0;
	old_stdin = -1; // dont forget echo
	int len = 0;
	while (args[len] != NULL)
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
				ft_putstr(1, "Minishell: ");
				ft_putstr(1, file_name);
				ft_putstr(1, ": No such file or directory\n");
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
		return fd;
	}
	if (in == 1)
	{
		dup2(fd, STDIN_FILENO);
		return fd;
	}
	return (0);
}

char **ft_realloc_2(char **old, size_t old_size, size_t new_size)
{
	char **new;
	int i;

	new = malloc(sizeof(char *) * (new_size + 1));
	i = 0;
	while (i < (int)old_size)
	{
		new[i] = old[i];
		i++;
	}
	return (new);
}

int search_second_quote(char *s, int start, char type)
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

char *replace_dollar(char *s, char *v, int start, int end)
{
	char *s1;
	char *s2;
	char *w;

	w = NULL;
	s1 = ft_substr(s, 0, start - 1);
	s2 = ft_substr(s, end, ft_strlen(s) - end);
	w = ft_strjoin(s1, v);
	w = ft_strjoin(w, s2);
	return (w);
}

char *handling_dollar(char *s, t_list *env_list)
{
	int i;
	int start;
	char *v;
	t_list *current;
	char *tmp;

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
					break;
				} // return (replace_dollar(s, current->env_value, start, i));
				current = current->next;
			}
			if (v[0] == '?' && v[1] == '\0')
				return (replace_dollar(v, "samurai", start, i));
		}
		i++;
	}
	return (s);
}

char **get_args(char *s, t_list *env_list)
{
	int i;
	int end;
	int start;
	char **args;

	start = 0;
	end = 0;
	i = 0;
	while (s[start])
	{
		if (s[start] == '\'' || s[start] == '\"')
		{
			if (s[start - 1] == '\\')
				continue;
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

int ft_exit(int fd, char **args)
{
	if (args[0] && !args[1])
	{
		exit(EXIT_SUCCESS);
	}
	if (args[1])
	{
		if (!ft_isdigit(args[1][0]))
		{
			ft_putstr(fd, "exit\n");
			ft_putstr(fd, "minishell: exit: ");
			ft_putstr(fd, args[1]);
			ft_putstr(fd, ": numeric argument required\n");
			exit(255);
		}
	}
	if (args[2])
	{
		ft_putstr(fd, "exit\n");
		ft_putstr(fd, "minishell: exit: too many arguments\n");
		return (1);
	}
	else
	{
		exit(ft_atoi(args[1]) % 256);
	}
	return (0);
}

char **get_env(t_list *env_list)
{
	t_list *current;
	char **env;
	int size = -1;

	current = env_list;
	while (current != NULL)
	{
		++size;
		env = ft_realloc_2(env, size, size + 1);
		env[size] = current->env;
		current = current->next;
	}
	env = ft_realloc_2(env, size, size + 1);
	env[size] = NULL;
	return env;
}

void    ft_execve_pip(char *str_pips, t_list *env_list)
{
    char *path;
    char **args;
    int args_len;
    int args_len_filtered;
    int i = 0;
	int stdout_fd = dup(1);
	int stdin_fd = dup(0);

	char **env = get_env(env_list);
    path = getcwd(path,0);
    args = get_args(str_pips, env_list);
    args_len = 0;
    args_len_filtered = 0;
    while (args[args_len])
        args_len++;
    if (update_out(args) == -1)
    {
		dup2(stdout_fd, 1);
		dup2(stdin_fd, 0);
		exit(EXIT_FAILURE);
	}
	if (args[0][0] == '\0'){
		dup2(stdout_fd, 1);
		dup2(stdin_fd, 0);
		exit(EXIT_FAILURE);
	}
    while (i < args_len)
    {
        if (args[i][0] != '\0')
            args_len_filtered++;
        i++;
    }
	// obtening path ----------------------
	path = check_fill_path(env_list, args);
	if (ft_strchr(args[0], '/'))
	{	
		path = args[0];
		if (args[0][0] == '.' && args[0][1] == '.')
		{
			char *pwd = NULL;
			if (chdir(args[0]) != 0)
				ft_putstr(1, "Error\n");
			pwd = getcwd(pwd, 0);
			searchch("PWD", pwd, env_list);
			searchch("OLDPWD", path, env_list);
		}
	}
	// --------------------------------------
    if (ft_strcmp("echo",args[0]) == 0){
        ft_echo(STDOUT_FILENO, args);
	}
	else if (ft_strcmp("exit", args[0]) == 0)
		ft_exit(1, args);
    else if (ft_strcmp("cd",args[0]) == 0){
        ft_cd(STDOUT_FILENO, args,env_list);
	}
    else if (ft_strcmp("pwd",args[0]) == 0){
        ft_pwd(STDOUT_FILENO);
	}
    else if (ft_strcmp("env",args[0]) == 0){
        ft_env(STDOUT_FILENO, env_list);
	}
    else if (ft_strcmp("unset",args[0]) == 0){
        ft_unset(args,env_list);
	}
    else if (ft_strcmp("export",args[0]) == 0){
        ft_export(STDOUT_FILENO, args,env_list);
	}
    else
    {
		if (path == NULL) // if the path is null and it is not a builtin
		{
			ft_putstr(1, "Minishell: ");
			ft_putstr(1, args[0]);
			ft_putstr(1, ": command not found\n");
			dup2(stdout_fd, 1);
			dup2(stdin_fd, 0);
			exit(EXIT_FAILURE);
		}
		char **_args = fill_paramlist(path, args, args_len, args_len_filtered);
		if (execve(path, _args, env) == -1)
		{
			ft_putstr(1, "Minishell: ");
			ft_putstr(1, args[0]);
			ft_putstr(1, ": No such file or directory\n");
		}
	}
	dup2(stdout_fd, 1);
	dup2(stdin_fd, 0);
    exit(EXIT_SUCCESS);
}

void    ft_execve_non_pip(char *str_pips, t_list *env_list, char **env)
{
    char *path;
    char **args;
    int args_len;
    int args_len_filtered;
    int i = 0;
	int updateout_fd;
	int stdout_fd = dup(1);
	int stdin_fd = dup(0);

	env = get_env(env_list);
    path = getcwd(path,0);
    args = get_args(str_pips, env_list);
    args_len = 0;
    args_len_filtered = 0;
    while (args[args_len])
        args_len++;
	updateout_fd = update_out(args);
	if (args[0][0] == '\0'){
		dup2(stdout_fd, 1);
		dup2(stdin_fd, 0);
		return;
	}
    if (updateout_fd == -1){
		dup2(stdout_fd, 1);
		dup2(stdin_fd, 0);
        return;
	}
    while (i < args_len)
    {
        if (args[i][0] != '\0')
            args_len_filtered++;
        i++;
    }
	// obtening path ----------------------
	path = check_fill_path(env_list, args);
	if (ft_strchr(args[0], '/'))
	{
		path = args[0];
		if (args[0][0] == '.' && args[0][1] == '.')
		{
			char *pwd = NULL;
			if (chdir(args[0]) != 0)
				ft_putstr(1, "Error\n");
			pwd = getcwd(pwd, 0);
			searchch("PWD", pwd, env_list);
			searchch("OLDPWD", path, env_list);
		}
	}
	// --------------------------------------
    if (ft_strcmp("echo",args[0]) == 0){
        ft_echo(STDOUT_FILENO, args);
	}
	else if (ft_strcmp("exit", args[0]) == 0)
		ft_exit(1, args);
    else if (ft_strcmp("cd",args[0]) == 0){
        ft_cd(STDOUT_FILENO, args,env_list);
	}
    else if (ft_strcmp("pwd",args[0]) == 0){
        ft_pwd(STDOUT_FILENO);
	}
    else if (ft_strcmp("env",args[0]) == 0){
        ft_env(STDOUT_FILENO, env_list);
	}
    else if (ft_strcmp("unset",args[0]) == 0){
        ft_unset(args,env_list);
	}
    else if (ft_strcmp("export",args[0]) == 0){
        ft_export(STDOUT_FILENO, args,env_list);
	}
    else
    {
		if (path == NULL) // if the path is null and it is not a builtin
		{
			ft_putstr(1, "Minishell: ");
			ft_putstr(1, args[0]);
			ft_putstr(1, ": command not found\n");
			dup2(stdout_fd, 1);
			dup2(stdin_fd, 0);
			return;
		}
		char **_args = fill_paramlist(path, args, args_len, args_len_filtered);
		if (fork() == 0)
		{
			if (execve(path, _args, env) == -1)
			{
				ft_putstr(1, "Minishell: ");
				ft_putstr(1, args[0]);
				ft_putstr(1, ": No such file or directory\n");
				exit(EXIT_FAILURE);
			}
		}
		wait(NULL);
	}
	dup2(stdout_fd, 1);
	dup2(stdin_fd, 0);
    return;
}

void ft_execve(char *str_pips, t_list *env_list)
{
	char *path;
	char **env;
	char **args;
	int args_len;
	int i;
	t_list *head;
	char **args1;
	pid_t pid;
	int status;

	env = get_env(env_list);

	i = 0;
	path = getcwd(path, 0);
	args = get_args(str_pips, env_list);
	args_len = 0;
	while (args[args_len] != NULL)
		args_len++;
	int r = update_out(args); // hadi khseha tkon lfooo9
	if (r == -1)
		return;
	if (args == NULL || args[0] == '\0')
		return;
	if (ft_strcmp("exit", args[0]) == 0)
		ft_exit(1, args);
	if (ft_strcmp("export", args[0]) == 0)
		return ft_export(STDOUT_FILENO, args, env_list);
	if (ft_strcmp("unset", args[0]) == 0)
		return ft_unset(args, env_list);
	if (ft_strcmp("cd", args[0]) == 0)
		return ft_cd(STDOUT_FILENO, args, env_list);
	if (ft_strcmp("pwd", args[0]) == 0)
		return ft_pwd(STDOUT_FILENO);
	if (ft_strcmp("env", args[0]) == 0)
		return ft_env(STDOUT_FILENO, env_list);
	if (ft_strcmp("echo", args[0]) == 0)
	{
		return ft_echo(STDOUT_FILENO, args);
	}
	path = check_fill_path(env_list, args);
	if (ft_strchr(args[0], '/'))
	{
		path = args[0];
		if (args[0][0] == '.' && args[0][1] == '.')
		{
			char *pwd = NULL;
			if (chdir(args[0]) != 0)
				ft_putstr(1, "Error\n");
			pwd = getcwd(pwd, 0);
			searchch("PWD", pwd, env_list);
			searchch("OLDPWD", path, env_list);
		}
	}
	if (path == NULL)
	{
		ft_putstr(1, "Minishell: ");
		ft_putstr(1, args[0]);
		ft_putstr(1, ": command not found\n");
		return;
	}
	int u = 0;
	char *str = "";
	while (u < args_len)
	{
		str = ft_strjoin(str, args[u]);
		str = ft_strjoin(str, " ");
		u++;
	}
	args = get_args(str, env_list);
	if (execve(path, args, env))
	{
		if (args[0][0] != '.' && args[0][1] != '.')
		{
			ft_putstr(1, "Minishell: ");
			ft_putstr(1, args[0]);
			ft_putstr(1, ": No such file or directory\n");
		}
	}
	exit(EXIT_SUCCESS);
}

int **ft_pipe(int pips)
{
	int **pipe_fd;
	int i;

	pipe_fd = (int **)malloc(pips * sizeof(int *));
	i = -1;
	while (++i < pips)
	{
		pipe_fd[i] = (int *)malloc(2 * sizeof(int));
		pipe(pipe_fd[i]);
	}
	return (pipe_fd);
}

void ft_close(int i, int pips, int **pipe_fd)
{
	int j;

	j = 0;
	while (j < pips)
	{
		if (j != i - 1)
			close(pipe_fd[j][0]);
		if (j != i)
			close(pipe_fd[j][1]);
		j++;
	}
}

void ft_free2d(int **arr, int i)
{
	while (i--)
		free(arr[i]);
	free(arr);
}

void handle_pipe(char **str_pips, t_list *env_list, int pips)
{
	int **pipe_fd;
	int status;
	int i;

	pipe_fd = ft_pipe(pips);
	i = -1;
	while (++i < pips + 1)
	{
		if (fork() == 0)
		{
			ft_close(i, pips, pipe_fd);
			if (i != 0)
				dup2(pipe_fd[i - 1][0], STDIN_FILENO);
			if (i != pips)
				dup2(pipe_fd[i][1], STDOUT_FILENO);
			ft_execve_pip(str_pips[i], env_list);
			ft_putstr(STDOUT_FILENO, 0);
			ft_close(-1, pips, pipe_fd);
		}
	}
	ft_close(-1, pips, pipe_fd);
	while (wait(&status) > 0)
		;
	// ft_free2d(pipe_fd, pips);
}

void handle_int(int sig_num)
{
	rl_on_new_line();
	ft_putstr(1, "\n");
	rl_replace_line("", 0);
	rl_redisplay();
}


void handle_int1(int sig_num)
{
	if (sig == 2)
		ft_putstr(1, "Quit: 3\n");
}

int main(int argc, char **argv, char **env)
{
	char *str;
	char **str_pip;
	t_list *env_list;
	pid_t pid;
	int pips;
	int i;
	int status;

	env_list = fill_env(env);
	signal(SIGQUIT, handle_int1);
	signal(SIGINT, handle_int);
	while (1)
	{

		str = readline(PROMPT);
		if (str == NULL)
			exit(0);
		pips = 0;
		i = 0;
		add_history(str);
		while (str[i] != '\0')
		{
			if (str[i] == '\'' || str[i] == '\"')
			{
				++i;
				while (str[i] != '\0')
				{
					if (str[i] == '\'' || str[i] == '\"')
						break;
					i++;
				}
			}
			if (str[i] == '|')
				pips++;
			i++;
		}
		// handle parsing errors such as redirections and heredocs also create all heredocs
		if (pips)
		{
			str_pip = ft_split(str, '|');
			handle_pipe(str_pip, env_list, pips);     //stdin : 0
		}
		else
		{
			
            ft_execve_non_pip(str, env_list, env);
            
		}
	}
	return (0);
}
