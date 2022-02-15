NAME = minishell
LIBFT =	Libft/libft.a
CC = gcc -g
INC = -I ./
SRCS =	srcs/*.c
FLAGS = -Wall -Wextra -Werror
# FLAGS =
OBJS = $(SRC:.c=.o)
all: $(NAME)
$(NAME): $(OBJS) $(LIBFT)
	@$(CC) $(FLAGS) -lreadline -L /Users/$(USER)/goinfre/.brew/opt/readline/lib -I /Users/$(USER)/goinfre/.brew/opt/readline/include $(INC) $(SRCS) -o $(NAME) $(LIBFT)
$(LIBFT):
	@make -C ./Libft
clean:
	@rm -f $(OBJS)
	@make clean -C ./libft
fclean: clean
	@rm -f $(NAME)
	@make fclean -C ./libft
re : fclean $(NAME)