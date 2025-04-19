CC = cc 

CFLAGS = -Wall -Werror -Wextra -Iincludes -fsanitize=address -g

LDFLAGS = -lreadline 

NAME = minishell

HEADER = includes/minishell.h 

SRCPARS =  srcs/parsing/handle_input.c lib/ft_lstadd_back.c lib/ft_lstlast.c \
	lib/ft_lstnew.c lib/ft_split.c lib/ft_strlen.c lib/ft_strcmp.c srcs/parsing/handle_syntax_error.c \
	srcs/parsing/handle_herdoc.c lib/ft_memcpy.c lib/ft_substr.c lib/ft_strlcpy.c lib/ft_strdup.c \
	lib/ft_isalnum.c srcs/parsing/handle_expand.c lib/ft_itoa.c 

SRC = srcs/execution/main.c srcs/execution/builtin/echo.c lib/ft_strncmp.c srcs/execution/builtin/cd.c \
	srcs/execution/free/free_args.c srcs/execution/get_cmd_path.c lib/ft_strjoin.c lib/ft_printf/ft_printf.c lib/ft_putchar_fd.c \
	lib/ft_putstr_fd.c lib/ft_cmdsize.c srcs/execution/her_doc.c srcs/execution/handle_single_command/handle_single_command.c \
	srcs/execution/handle_multiple_command/handle_multiple_command.c srcs/execution/builtin/is_builtin.c srcs/execution/builtin/pwd.c \
	srcs/execution/builtin/env.c srcs/execution/builtin/unset.c srcs/execution/builtin/export.c srcs/execution/fill_env_struct.c \
	lib/ft_isalpha.c srcs/execution/utils.c srcs/execution/handle_redirections/handle_redirections_single.c srcs/execution/handle_redirections/handle_redirections_multiple.c 


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