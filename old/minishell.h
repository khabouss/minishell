/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majdahim <majdahim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 14:04:30 by majdahim          #+#    #+#             */
/*   Updated: 2022/01/07 19:06:20 by majdahim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
// #include <readline/readline.h>
#include "libft/libft.h"
// #include <readline/history.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <signal.h>
#include <readline/readline.h>
#include <errno.h>
#include <readline/history.h>

#define PROMPT "minishell> "
#define ENTRECODE printf("ENTRE CODE\n");

typedef struct s_list {
  char  **args;
  char  *env;
  char  *env_key;
  char  *env_value;
  char  *path;
  int   check_dollar;
  struct s_list * next;
} t_list;
int	ft_execve(char *str_pips, t_list *env_list, char **env);
t_list	*fill_env(char **env);
char	*replace_dollar(char *s, char *v, int start, int end);
char	*handling_dollar(char *s, t_list *env_list);
int	search_second_quote(char *s, int start, char type);
char	**get_args(char *s, t_list *env_list);
int	ft_echo(int fd, char **args, t_list *env_list);
int	ft_strcmp(char *s1, char *s2);
char	**ft_realloc_2(char **old, size_t old_size, size_t new_size);
void	ft_putchar(int fd, char c);
void	ft_putstr(int fd, char *s);
int		ft_strlen2(char **w);
int	ft_pwd(int fd);
int	ft_env(int fd, t_list *env_list);
void	ft_cd(int fd, char **args, t_list *env_list);
void	searchch(char *word, char *changed, t_list *env_list);
char	*get_home_incd(t_list *env_list);
int	ft_export(int fd, char **args, t_list *env_list);
void	addto_list(char *args, t_list *env_list);
void	ft_lstadd_back(t_list **env_list, t_list *new);
t_list	*add_content(char **content);
void	print_list(int fd, t_list *env_list);
int	ft_unset(char **args, t_list *env_list);
void	delet_v_env(t_list *env_list, char *argv);
int	ft_exit(int fd, char **args);
char	*check_fill_path(t_list *env_list, char **args);
void ft_execve1(t_list *env_list, char **args,char **env);
void	handle_int1(int sig_num);
void	handle_int(int sig_num);
void	handle_int01(int sig_num);
int sig;


#endif