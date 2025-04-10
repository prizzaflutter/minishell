CC = cc 

CFLAGS = -Wall -Werror -Wextra -Iincludes

NAME = minishell

HEADER = includes/minishell.h 

SRC = srcs/execution/builtin/echo.c srcs/execution/main.c lib/ft_strncmp.c srcs/execution/builtin/cd.c \
		srcs/execution/free/free_args.c srcs/execution/get_cmd_path.c lib/ft_split.c lib/ft_strjoin.c lib/ft_strlen.c \

SRCPARS = srcs/parsing/parsing.c srcs/parsing/main.c lib/ft_lstadd_back.c lib/ft_lstlast.c lib/ft_lstnew.c lib/ft_split.c 

OBJ = $(SRC:%.c=%.o)
OBJPARS = $(SRCPARS:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJ) $(OBJPARS)  $(HEADER)
	$(CC) $(CFLAGS) $(OBJ) $(OBJPARS) -lreadline  -o $(NAME) 

%.o: %.c 
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ) $(OBJPARS) 

fclean: clean
	rm -f $(NAME)

re: fclean all