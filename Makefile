CC = cc 

CFLAGS = -Wall -Werror -Wextra -Iincludes

NAME = minishell

HEADER = includes/minishell.h 

SRC = srcs/execution/builtin/echo.c srcs/execution/main.c lib/ft_strncmp.c 

SRCPARS = 

OBJ = $(SRC:%.c=%.o)
OBJPARS = $(SRCPARS:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJ) $(HEADER)
	$(CC) $(CFLAGS) $(OBJ) $(OBJPARS) -o $(NAME) 

%.o: %.c 
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ) $(OBJPARS)


re: fclean all