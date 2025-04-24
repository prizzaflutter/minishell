CC = cc 

CFLAGS = -Wall -Werror -Wextra -Iincludes -g #-fsanitize=address -g

LDFLAGS = -lreadline 

NAME = minishell

HEADER = includes/minishell.h 

SRCPARS = srcs/parsing/main.c  srcs/parsing/handle_input.c lib/ft_lstadd_back.c lib/ft_lstlast.c \
	lib/ft_lstnew.c lib/ft_split.c lib/ft_strlen.c lib/ft_strcmp.c srcs/parsing/handle_syntax_error.c \
	srcs/parsing/handle_herdoc.c lib/ft_memcpy.c lib/ft_substr.c lib/ft_strlcpy.c lib/ft_isdigit.c \
	lib/ft_isalnum.c srcs/parsing/handle_expand.c lib/ft_itoa.c srcs/parsing/handle_list_commands.c

SRC =  srcs/execution/execute_command.c srcs/execution/builtin/echo.c lib/ft_strncmp.c srcs/execution/builtin/cd.c \
	srcs/execution/get_cmd_path.c lib/ft_strjoin.c lib/ft_printf/ft_printf.c lib/ft_putchar_fd.c \
	lib/ft_putstr_fd.c lib/ft_cmdsize.c srcs/execution/her_doc.c srcs/execution/handle_single_command/handle_single_command.c \
	srcs/execution/handle_multiple_command/handle_multiple_command.c srcs/execution/builtin/is_builtin.c srcs/execution/builtin/pwd.c \
	srcs/execution/builtin/env.c srcs/execution/builtin/unset.c srcs/execution/builtin/export.c srcs/execution/fill_env_struct.c \
	lib/ft_isalpha.c srcs/execution/utils.c srcs/execution/handle_redirections/handle_redirections_single.c srcs/execution/handle_redirections/handle_redirections_multiple.c \
	srcs/execution/garbage_collector/gc_clear.c srcs/execution/garbage_collector/gc_malloc.c srcs/execution/garbage_collector/gc_strdup.c \
	srcs/execution/garbage_collector/gc_strndup.c srcs/execution/garbage_collector/gc_exist.c lib/gc_strcat.c lib/gc_split.c lib/ft_bzero.c lib/ft_calloc.c  lib/gc_strjoin.c lib/gc_strcpy.c lib/ft_strchr.c \
	srcs/execution/handle_single_command/built_in_check.c srcs/execution/builtin/built_in_helper.c srcs/execution/exit_status.c


OBJ = $(SRC:%.c=%.o)
OBJPARS = $(SRCPARS:%.c=%.o)

all: $(NAME)

valgrind: $(NAME)
	valgrind --leak-check=full --track-origins=yes ./$(NAME)

$(NAME): $(OBJ) $(OBJPARS) $(HEADER)
	$(CC) $(CFLAGS) $(OBJ) $(OBJPARS) $(LDFLAGS) -o $(NAME)

%.o: %.c 
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ) $(OBJPARS)

fclean: clean
	rm -f $(NAME)

re: fclean all