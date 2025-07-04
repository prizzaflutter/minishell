CC = cc

CFLAGS = -Wall -Werror -Wextra -Iincludes -g #-fsanitize=address -g

LDFLAGS = -lreadline 

NAME = minishell

HEADER = includes/minishell.h 

SRCPARS = srcs/parsing/main.c srcs/parsing/main_utilis.c srcs/parsing/handle_input.c srcs/parsing/handle_list_tokens.c \
	srcs/parsing/handle_syntax_error.c srcs/parsing/handle_herdoc.c srcs/parsing/handle_list_commands.c srcs/parsing/main_utilis_one.c\
	srcs/parsing/handle_list_commands_utilis.c srcs/parsing/handle_signals.c srcs/parsing/add_space_to_inputs.c \
	srcs/parsing/handle_herdoc_utilis.c srcs/parsing/handle_input_utilis.c\
	srcs/parsing/handle_herdoc_expand.c srcs/parsing/handle_expand_utilis.c srcs/parsing/handle_input_utilis_one.c \
	srcs/parsing/handle_input_utilis_two.c srcs/parsing/handle_input_utilis_three.c srcs/parsing/handle_input_utilis_four.c \
	lib/ft_split_expand.c lib/ft_split_expand_utilis.c lib/ft_isalnum.c srcs/parsing/handle_expand.c lib/ft_itoa.c \
	lib/ft_split.c lib/ft_split_utilis.c lib/ft_memcpy.c lib/ft_substr.c lib/ft_strlcpy.c lib/ft_isdigit.c \
	lib/ft_strlen.c lib/ft_strcmp.c

SRC = srcs/execution/execute_command.c srcs/execution/builtin/echo.c lib/ft_strncmp.c srcs/execution/builtin/cd/cd.c \
	srcs/execution/path_configuration/get_cmd_path.c lib/ft_strjoin.c lib/ft_printf/ft_printf.c lib/ft_putchar_fd.c \
	lib/ft_putstr_fd.c lib/ft_cmdsize.c  srcs/execution/handle_single_command/handle_single_command.c \
	srcs/execution/handle_multiple_command/handle_multiple_command.c srcs/execution/builtin/is_builtin.c srcs/execution/builtin/pwd.c \
	srcs/execution/builtin/env.c srcs/execution/builtin/unset.c  srcs/execution/fill_env_struct.c \
	lib/ft_isalpha.c srcs/execution/utils.c srcs/execution/handle_redirections/handle_redirections_single.c \
	srcs/execution/handle_redirections/handle_redirections_multiple.c srcs/execution/garbage_collector/gc_clear.c \
	srcs/execution/garbage_collector/gc_malloc.c srcs/execution/garbage_collector/gc_strdup.c \
	srcs/execution/garbage_collector/gc_strndup.c srcs/execution/garbage_collector/gc_exist.c lib/gc_strcat.c lib/gc_split.c \
	lib/ft_bzero.c lib/ft_calloc.c  lib/gc_strjoin.c  lib/ft_strchr.c srcs/execution/handle_single_command/built_in_check.c \
	srcs/execution/exit_status.c lib/ft_lstnew_stack.c lib/ft_lstadd_back_stack.c lib/ft_strnstr.c lib/ft_lstnew_copy.c lib/ft_lstadd_front_copy.c\
	srcs/execution/builtin/exit.c srcs/execution/builtin/cd/add_to_path.c srcs/execution/builtin/cd/go_up.c srcs/execution/builtin/cd/normalize.c \
	srcs/execution/builtin/cd/update_old_pwd.c srcs/execution/builtin/export/export.c srcs/execution/builtin/export/no_args.c  srcs/execution/builtin/export/export_utils.c \
	srcs/execution/builtin/export/export_exit.c srcs/execution/builtin/cd/cd_utilits.c  srcs/execution/path_configuration/is_path_exist.c \
	lib/ft_lstadd_back_copy.c lib/ft_atoi.c srcs/execution/handle_multiple_command/process.c srcs/execution/handle_redirections/redirection_utilits.c


OBJ = $(SRC:%.c=%.o)
OBJPARS = $(SRCPARS:%.c=%.o)

all: $(NAME)

valgrind: $(NAME)
	valgrind --leak-check=full --track-origins=yes ./$(NAME) 
fdvalgrind: $(NAME)
	valgrind --leak-check=full --track-fds=yes ./$(NAME) 

$(NAME): $(OBJ) $(OBJPARS) $(HEADER)
	$(CC) $(CFLAGS) $(OBJ) $(OBJPARS) $(LDFLAGS) -o $(NAME)

%.o: %.c 
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ) $(OBJPARS)

fclean: clean
	rm -f $(NAME)

re: fclean all
