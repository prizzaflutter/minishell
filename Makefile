CC = cc 

CFLAGS = -Wall -Werror -Wextra -Iincludes

NAME = minishell

HEADER = includes/minishell.h 

SRCSPARS = srcs/parsing/test1.c 
SRCSEXEC = srcs/execution/test.c srcs/execution/main.c

OBJSPAR = $(SRCSPARS:srcs/parsing/%.c=obj/%.o) 
OBJSEXEC = $(SRCSEXEC:srcs/execution/%.c=obj/%.o)

OBJ = $(OBJSPAR) $(OBJSEXEC)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) 

obj/%.o: srcs/parsing/%.c $(HEADER)
	@mkdir -p obj
	$(CC) $(CFLAGS) -c $< -o $@

obj/%.o: srcs/execution/%.c $(HEADER)
	@mkdir -p obj
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf obj

fclean: clean
	rm -f $(NAME)

re: fclean all