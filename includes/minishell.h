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

typedef struct s_command {
	char **cmd;
	char **inoutfile;
	void *next; 
	void *prev;
} t_command;

enum token_type {
	WORD, // normal word
	PIPE, // |
	REDIR_IN, // <
	REDIR_OUT, // >
	HEREDOC, // <<
	APPEND // >>
};

typedef struct s_token {
	char *str;
	enum token_type type;
	struct s_token *next;
} t_token;


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
char	*ft_strdup(const char *s1);
char	*ft_substr(char const *s, unsigned int start, size_t len);
void	*ft_memcpy(void *dst, const void *src, size_t n);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlen(const char *s);
int		ft_isalnum(int c);
char	*add_space_inputs(char *str);
int		ft_strcmp(const char *s1, const char *s2);
int		add_command_element(char *str, t_token **tokens);
int		define_token_type(char *str);
int		handle_unexpected_token(t_token *tokens);
int		handle_herdocs(t_token *t_token);
int		handle_herdoc_input(char *str);
char *handle_expand(char *str);

#endif