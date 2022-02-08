NAME = minishell
LIBFT =	Libft/libft.a
CC = gcc -g
INC = -I ./
SRCS =	*.c
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