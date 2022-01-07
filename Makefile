NAME = minishell
LIBFT =	Libft/libft.a
CC = gcc -g
INC = -I ./
SRCS =main.c ft_echo.c get_args.c minishell_utils.c ft_pwd.c ft_env.c ft_cd.c ft_export.c ft_unset.c ft_exit.c get_path_exec.c ft_signals.c
# FLAGS = #-Wall -Wextra -Werror -g 
# FLAGS =
USER = majdahim
OBJS = $(SRC:.c=.o)
all: $(NAME)
$(NAME): $(OBJS) $(LIBFT)
	@$(CC) -lreadline -L /Users/$(USER)/goinfre/.brew/opt/readline/lib -I /Users/$(USER)/goinfre/.brew/opt/readline/include $(INC) $(SRCS) -o $(NAME) $(LIBFT)
$(LIBFT):
	@make -C ./Libft
clean:
	@rm -f $(OBJS)
	@make clean -C ./libft
fclean: clean
	@rm -f $(NAME)
	@make fclean -C ./libft
re : fclean $(NAME)