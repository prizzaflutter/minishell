CC = cc 

CFLAGS = -Wall -Werror -Wextra -Iincludes

NAME = minishell

HEADER = includes/minishell.h 

SRC = srcs/execution/builtin/echo.c

SRCPARS = srcs/parsing/parse.c srcs/parsing/main.c lib/ft_lstadd

OBJ = $(SRC:%.c=%.o)
OBJPARS = $(SRCPARS:%.c=%.o)
all: $(NAME)

$(NAME): $(OBJ) $(HEADER)
	$(CC) $(CFLAGS) $(OBJ) $(OBJPARS) -o $(NAME) 

%.o: %.c 
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ) $(OBJPARS)

fclean: clean
	rm -f $(NAME)

re: fclean all