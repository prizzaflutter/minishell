CC = cc 

CFLAGS = -Wall -Werror -Wextra -Iincludes

LDFLAGS = -lreadline 

NAME = minishell

HEADER = includes/minishell.h 



SRCPARS = srcs/parsing/main.c srcs/parsing/handle_input.c lib/ft_lstadd_back.c lib/ft_lstlast.c \
	lib/ft_lstnew.c lib/ft_split.c lib/ft_strlen.c lib/ft_strcmp.c

SRC = srcs/execution/builtin/echo.c lib/ft_strncmp.c srcs/execution/builtin/cd.c \
		srcs/execution/free/free_args.c srcs/execution/get_cmd_path.c lib/ft_strjoin.c lib/ft_printf/ft_printf.c lib/ft_putchar_fd.c \
		lib/ft_putstr_fd.c lib/ft_cmdsize.c 

OBJ = $(SRC:%.c=%.o)
OBJPARS = $(SRCPARS:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJ) $(OBJPARS) $(HEADER)
	$(CC) $(CFLAGS) $(OBJ) $(OBJPARS) $(LDFLAGS) -o $(NAME) 

%.o: %.c 
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ) $(OBJPARS) 

fclean: clean
	rm -f $(NAME)

re: fclean all