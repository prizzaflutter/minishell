CC = cc 

CFLAGS = -Wall -Werror -Wextra -Iincludes

NAME = minishell

HEADER = includes/minishell.h 

SRC = srcs/execution/builtin/echo.c srcs/execution/main.c 

OBJ = $(SRC:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJ) $(HEADER)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) 

%.o: %.c 
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all