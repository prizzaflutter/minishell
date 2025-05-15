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
# include <stdint.h>
# include <signal.h>


///@brief  those struct for garbage collector

//---------------------------------
typedef struct  s_gc_node {
	void *ptr;
    int is_token;
	struct s_gc_node *next;
} t_gc_node;

typedef struct s_gc {
	t_gc_node *head;
} t_gc;
//--------------------------------

typedef struct s_stack {
	char *path;
	struct s_stack *next;
}t_stack;

typedef struct s_command {
	char **cmd;
	char **inoutfile;
	int  fd_in;
	void *next; 
	void *prev;
} t_command;

typedef struct s_env{
	char *key;
	char *value;
	struct s_env *next;
} t_env;

typedef struct s_copy{
	char *key;
	char *value;
	struct s_copy *next;
}t_copy;

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
	int fd_herdoc;
	struct s_token *next;
	struct s_token *prev;
} t_token;

typedef struct s_quote{
	int		is_quote;
	char	quote_char;
}t_quote;

typedef struct g_herdoc_h{
	int		fd;
	int		fd1;
	int		status;
	pid_t	pid;
} t_herdoc_h;

// EXEC FUNCTIONS
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	my_echo(char **argv);
char	*make_path(t_gc *gc, char **paths, char **tmp);
char	*get_cmd_path(t_gc *gc, char *cmd, t_env *env);
void	ft_printf(int fd, const char *format, ...);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
int		ft_cmdsize(t_command *cmd);
char	*configure_path(t_gc *gc, char *cmd, t_env *env);
void	handle_single_command(t_gc *gc,t_command *cmd, t_env *env);
int		handle_multiple_command(t_gc *gc, t_command *cmd, t_env *env);
char	*is_builtin (char *cmd);
int		my_cd(t_gc *gc, t_env *env, char *argv);
void	my_pwd(t_env *env);
void	my_env(t_env *env);
void	my_unset(t_env **env, char **argv);
void	ft_lstadd_front_env(t_env **env, t_env *new_env);
void	my_export(t_gc *gc, t_env **env, char **cmd_args);
t_env	*fill_env (t_gc *gc, char **envp);
int		ft_isalpha(int a);
int		is_valid_identifier(const char *str);
char	**convert_env_to_array(t_gc *gc, t_env *env);
int handle_redirections_single (t_command *cmd);
int		handle_redirections_multiple(t_command *current_cmd, int fd_array[]);
void	*gc_malloc(t_gc *gc, size_t size, int is_token);
void	gc_clear(t_gc *gc, int is_token);
char	*ft_strchr(const char *s, int c);
char	*gc_strndup(t_gc *gc, const char *str, size_t n);
char	*gc_strdup(t_gc *gc, const char *str);
char	*gc_strcpy(t_gc *gc, char const *str, char charset);
char	*gc_strcat(t_gc *gc, char *dst, const char *src);
char	*gc_strjoin(t_gc *gc, char const *s1, char const *s2);
int		gc_exist(t_gc *gc, void *ptr);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(t_gc *gc, size_t count, size_t size);
char	**gc_split(t_gc *gc, char const *s, char c);
int		is_on_parent(char *build_in_f, t_command *cmd, t_env *env, t_gc *gc);
int		is_on_child(char *build_in_f, t_command *cmd, t_env *env, t_gc *gc);
char	**split_key_value(t_gc *gc, char *str, int *is_append);
int 	is_valid_identifier(const char *str);
void	no_args(t_env *env, t_gc *gc);
void	add_new_env(char *key, char *value, t_gc *gc, t_env **env);
void	update_value(char **key_value, t_env **env, t_gc *gc, int is_append);
int		is_builtin_excute(t_gc *gc, t_env **env, t_command *cmd);
int		exit_status(int set, int new_status);
void	execute_command(t_gc *gc, t_command *cmd, t_env *env);
void	save_int_out(int *org_int, int *org_out);
void	restore_in_out(int *org_int, int *org_out);
void	print_command_list(t_command *cmds);
void	ft_lstadd_back_stack(t_stack **stack, t_stack *new);
t_stack	*ft_lstnew_stack(t_gc *gc, void	*content);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
void	ft_lstadd_front_copy(t_copy **copy, t_copy *new_copy);
t_copy	*ft_lstnew_copy(t_gc *gc, void	*key, void *value);
void	my_exit(char **args);
char	*normalize_path (t_env *env, t_gc *gc, char *path, int flag);
void	go_up(t_stack **stack);
void	add_to_path(t_gc *gc,char *path, t_stack **stack);
void	update_oldpwd(t_gc *gc, t_env *env, char *oldpwd);
void	no_args(t_env *env, t_gc *gc);
void	ft_lstadd_back_copy(t_copy **copy, t_copy *new);
int		ft_atoi(const char *str);
char	*is_overflow(int set, char	*new_status);
int		redirection_checker(t_command *cmd, int *in, int *out, int i);
int		child_precess(t_command *current_cmd, int *prev_fd, int *fd_array);
void	parent_process(t_command *current_cmd, int *prev_fd, int *fd_array);


// PARSING FUNCTIONS
t_token	*ft_lstnew(t_gc *gc, char *content, int flag);
void	ft_lstadd_back(t_token **lst, t_token *new);
t_token	*ft_lstlast(t_token *lst);
char	**ft_split(t_gc *gc, char const *str);
int		count_words(char const *str);
char	*ft_substr(t_gc *gc,char const *s, unsigned int start, size_t len);
void	*ft_memcpy(void *dst, const void *src, size_t n);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
char	*ft_strjoin(t_gc *gc, char const *s1, char const *s2);
size_t	ft_strlen(const char *s);
int		ft_isalnum(int c);
char	*ft_itoa(t_gc *gc, int n);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_isalpha(int c);
int     ft_isdigit(int c);
int		ft_is_only_whitespace(char *str);
char	*add_space_inputs(t_gc *gc, char *str);
int		add_command_element(t_gc *gc,char *str, t_token **tokens, t_env *env);
char	*handle_double_single_quotes(t_gc *gc, char *str);
int		define_token_type(char *str);
int		handle_unexpected_token(t_token *tokens);
int		handle_unclosed_quotes(char *str);
int		handle_herdocs(t_gc *gc, t_token *t_token, t_env *env);
int		handle_herdoc_input(t_gc *gc, char *str, t_token *token, t_env *env);
char	*handle_delemitre(t_gc *gc, char *str);
char	*handle_expand_generale(t_gc *gc, char *str, int flag, t_env *env);
int		detect_quotes(char *str, int flag);

char	*handle_double_single_quotes(t_gc *gc, char *str);
void	build_command_list(t_gc *gc, t_token *tokens, t_command **cmd_list);

char	**get_inoutfile(t_gc *gc, t_token *tokens);
char	**get_commands(t_gc *gc, t_token *tokens);
int		get_herdoc_fd(t_token *tokens);
void	close_herdoc_fd(t_token **tokens);
//signals
void call_signals(void);
void	calll_herdoc_signals(void);
// PRINTING FUNCTIONS
void print_list(t_token *tokens);
void call_read_from_heredoc_fd(t_token *tokens);
void print_command_list(t_command *cmds);

#endif
