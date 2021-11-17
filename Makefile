NAME = minishell
LIBFT =	libft/libft.a
CC = gcc
INC = -I ./
SRCS =	*.c
# FLAGS = #-Wall -Wextra -Werror -g 
# FLAGS =
OBJS = $(SRC:.c=.o)
all: $(NAME)
$(NAME): $(OBJS) $(LIBFT)
	@$(CC) -lreadline $(INC) $(SRCS) -o $(NAME) $(LIBFT) 
$(LIBFT):
	@make -C ./libft
clean:
	@rm -f $(OBJS)
	@make clean -C ./libft
fclean: clean
	@rm -f $(NAME)
	@make fclean -C ./libft
re : fclean $(NAME)