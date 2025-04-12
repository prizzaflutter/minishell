#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <limits.h>
# include <stdarg.h>
# include "../lib/get_next_line/get_next_line.h"

typedef struct s_command {
	char **cmd;
	char **inoutfile;
	void *next; 
	void *prev;
} t_command;

typedef struct s_token {
	char *str;
	int type;
	struct s_token *next;
} t_token;

enum token_type {
	WORD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	HEREDOC,
	APPEND
};

// EXEC FUNCTIONS
int	ft_strncmp(const char *s1, const char *s2, size_t n);
void my_echo(char **argv);
int my_cd (char **argv);
char	*make_path(char **paths, char **tmp);
char	*get_cmd_path(char *cmd, char**env);
void	free_args(char **cmd_args);
void	ft_printf(int fd, const char *format, ...);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
int		ft_cmdsize(t_command *cmd);
int		handle_herdoc_infile(t_command *cmd);



// PARSING FUNCTIONS
t_token	*ft_lstnew(char *content);
void	ft_lstadd_back(t_token **lst, t_token *new);
t_token	*ft_lstlast(t_token *lst);
char	**ft_split(char const *str, char charset);
char	*add_space_inputs(char *str);
#endif