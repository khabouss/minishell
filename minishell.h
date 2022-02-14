/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majdahim <majdahim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 19:54:48 by tkhabous          #+#    #+#             */
/*   Updated: 2022/02/14 13:51:51 by majdahim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <string.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <errno.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <unistd.h>
# include <stdlib.h> 
# define PROMPT "minishell> "
# define ENTRECODE printf("ENTRE CODE\n");

typedef struct s_list
{
	char			**args;
	char			*env;
	char			*env_key;
	char			*env_value;
	char			*path;
	struct s_list	*next;
}					t_list;

int		ft_strcmp(char *s1, char *s2);
int		ft_strlen2(char **w);
void	ft_putstr(int fd, char *s);
void	ft_echo(int fd, char **args);
void	ft_pwd(int fd);
void	ft_env(int fd, t_list *env_list);
void	ft_cd(int fd, char **args, t_list *env_list);
char	*get_home_incd(t_list *env_list);
void	searchch(char *word, char *changed, t_list *env_list);
void	print_list(int fd, t_list *env_list);
t_list	*add_content(char **content);
void	ft_lstadd_back(t_list **env_list, t_list *new);
void	addto_list(char *args, t_list *env_list);
void	ft_export(int fd, char **args, t_list *env_list);
int		ft_exit(int fd, char **args);
void	ft_execve(char *str_pips, t_list *env_list);
void	ft_execve_non_pip(char *str_pips, t_list *env_list, char **env);
char	**get_args(char *s, t_list *env_list);
char	**ft_realloc_2(char **old, size_t old_size, size_t new_size);
char	*handling_dollar(char *s, t_list *env_list);
char	*replace_dollar(char *s, char *v, int start, int end);
int		search_second_quote(char *s, int start, char type);
char	**fill_paramlist(char *path, char **args, int len, int len_filtered);
char	*check_fill_path(t_list *env_list, char **args);
void	delet_v_env(t_list *env_list, char *argv);
void	ft_unset(char **args, t_list *env_list);
char	**get_env(t_list *env_list);
int		update_out(char **args);
int		ft_heredoc(char **args, int i, int old);
void	handle_int1(int sig_num);
void	handle_int(int sig_num);
int		g_sig;
t_list	*fill_env(char **env);
void	handle_pipe(char **str_pips, t_list *env_list, int pips);
int		**ft_pipe(int pips);
void	ft_execve_pip(char *str_pips, t_list *env_list);
void	ft_close(int i, int pips, int **pipe_fd);
void	free_t2(char **w);
void	ft_free2d(int **arr, int i);
void	ft_putchar(int fd, char c);

#endif
