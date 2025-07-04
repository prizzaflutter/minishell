/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykassim <aykassim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 11:02:27 by iaskour           #+#    #+#             */
/*   Updated: 2025/06/22 16:46:15 by aykassim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
# include <signal.h>
# include <sys/stat.h>
# include <errno.h>

typedef struct s_gc_node
{
	void				*ptr;
	int					is_token;
	struct s_gc_node	*next;
}	t_gc_node;

typedef struct s_gc
{
	t_gc_node	*head;
}	t_gc;

typedef struct s_stack
{
	char			*path;
	struct s_stack	*next;
}	t_stack;

typedef struct s_command
{
	char	**cmd;
	char	**inoutfile;
	int		fd_in;
	void	*next;
	void	*prev;
}	t_command;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_copy
{
	char			*key;
	char			*value;
	struct s_copy	*next;
}	t_copy;

enum e_token_type
{
	WORD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	HEREDOC,
	APPEND
};

typedef struct s_token
{
	char				*str;
	enum e_token_type	type;
	int					fd_herdoc;
	struct s_token		*next;
	struct s_token		*prev;
}	t_token;

typedef struct s_quote
{
	int		is_quote;
	char	quote_char;
}	t_quote;

typedef struct g_herdoc_h
{
	int		fd;
	int		fd1;
	int		status;
	pid_t	pid;
}	t_herdoc_h;

typedef struct g_add_space
{
	int		isq;
	char	quote_char;
	int		len;
	int		cm;
	int		i;
	int		j;
}	t_add_space;

typedef struct g_compute_length
{
	int		i;
	int		len;
	int		is_sq;
	int		is_dq;
}	t_compute_length;

typedef struct g_var_expand
{
	char	*res;
	int		i;
	int		k;
	int		is_squote;
	int		is_dquote;
	int		is_her;
}	t_var_expand;

typedef struct g_str_inputs
{
	char	*str;
	char	*export;
	char	*echo_str;
	char	*exp_str;
}	t_str_inputs;

typedef struct g_main_var
{
	t_gc		*gc;
	t_env		*ens;
	t_token		*tokens;
	t_command	*cmds;
	char		*input;
	int			fd;
}	t_main_var;

typedef struct g_count_w_expand
{
	int		i;
	int		cm;
	char	quote_char;
}	t_count_w_expand;

typedef struct s_proccess_context
{
	t_gc	*gc;
	t_env	**env;
	int		*flag_sint;
	int		*flag_squit;
}	t_process_context;

int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	my_echo(char **argv);
char	*make_path(t_gc *gc, char **paths, char **tmp);
char	*get_cmd_path(t_gc *gc, char *cmd, t_env *env);
void	ft_printf(const char *format, ...);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
int		ft_cmdsize(t_command *cmd);
char	*configure_path(t_gc *gc, char *cmd, t_env *env);
void	handle_single_command(t_gc *gc, t_command *cmd, t_env **env);
int		handle_multiple_command(t_process_context *ctx, t_command *cmd);
char	*is_builtin(char *cmd);
int		my_cd(t_gc *gc, t_env **env, char **argv, int is_pipe);
void	my_pwd(t_env *env);
void	my_env(t_env *env);
void	my_unset(t_env **env, char **argv);
void	ft_lstadd_front_env(t_env **env, t_env *new_env);
void	my_export(t_gc *gc, t_env **env, char **cmd_args, int is_pipe);
t_env	*fill_env(t_gc *gc, char **envp);
char	**convert_env_to_array(t_gc *gc, t_env *env);
int		handle_redirections_single(t_command *cmd);
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
int		is_on_parent(char *build_in_f, t_command *cmd, t_env **env, t_gc *gc);
int		is_on_child(char *build_in_f, t_command *cmd, t_env *env, t_gc *gc);
char	**split_key_value(t_gc *gc, char *str, int *is_append);
int		is_valid_identifier(const char *str);
void	no_args(t_env *env, t_gc *gc);
void	add_new_env(char *key, char *value, t_gc *gc, t_env **env);
void	update_value(char **key_value, t_env **env, t_gc *gc, int is_append);
int		is_builtin_excute(t_gc *gc, t_env **env, t_command *cmd);
int		exit_status(int set, int new_status);
void	execute_command(t_gc *gc, t_command *cmd, t_env **env);
void	save_int_out(int *org_int, int *org_out);
void	restore_in_out(int *org_int, int *org_out);
void	ft_lstadd_back_stack(t_stack **stack, t_stack *new);
t_stack	*ft_lstnew_stack(t_gc *gc, void	*content);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
void	ft_lstadd_front_copy(t_copy **copy, t_copy *new_copy);
t_copy	*ft_lstnew_copy(t_gc *gc, void	*key, void *value);
void	my_exit(char **args, int is_pip);
char	*normalize_path(t_env *env, t_gc *gc, char *path);
void	go_up(t_stack **stack);
void	add_to_path(t_gc *gc, char *path, t_stack **stack);
void	update_oldpwd(t_gc *gc, t_env **env, char *oldpwd);
void	ft_lstadd_back_copy(t_copy **copy, t_copy *new);
int		ft_atoi(const char *str);
char	*is_overflow(int set, char	*new_status);
int		redirection_checker(t_command *cmd, int *out_file, int i);
int		child_precess(t_command *current_cmd, int *prev_fd, int *fd_array);
void	parent_process(t_command *current_cmd, int *prev_fd, int *fd_array);
char	*gc_strjoin_1(t_gc *gc, char const *s1, char const *s2);
t_env	*ft_lstnew_env(t_gc *gc, void	*key, void *value);
void	export_exit(int has_error, int is_pipe);
int		get_len(char **argv);
int		is_absolute_path(char *path);
int		to_manay_args(int len, int is_pipe);
void	cd_alone(t_gc *gc, t_env **env, int is_pipe);
int		is_path_exist(t_env *env);
int		handle_append_redir(t_command *cmd, int *out_file, int i);
int		handle_trunc_redir(t_command *cmd, int *out_file, int i);
int		handle_input_redir(t_command *cmd, int i);
int		handle_herdoc_redir(t_command *cmd);
t_token	*ft_lstnew(t_gc *gc, char *content, int flag, int quote);
void	ft_lstadd_back(t_token **lst, t_token *new);
t_token	*ft_lstlast(t_token *lst);
char	**ft_split(t_gc *gc, char const *str);
int		count_words(char const *str);
char	*ft_substr(t_gc *gc, char const *s, unsigned int start, size_t len);
void	*ft_memcpy(void *dst, const void *src, size_t n);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
char	*ft_strjoin(t_gc *gc, char const *s1, char const *s2);
size_t	ft_strlen(const char *s);
int		ft_isalnum(int c);
char	*ft_itoa(t_gc *gc, int n);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_is_only_whitespace(char *str);
int		check_quote(char str, int *is_quote, char *quote_char);
char	*add_space_inputs(t_gc *gc, char *str);
int		add_command_element(t_gc *gc, char *str, t_token **tokens, t_env *env);
char	*handle_double_single_quotes(t_gc *gc, char *str);
int		its_have_dollar_signe(char *str);
void	add_element_to_tokens(t_gc *gc, t_token **tokens, char *str);
void	add_element_to_listcopy(t_gc *gc, char *str, t_token **tokens_tmp);
void	handle_val_before_addtokens(t_gc *gc, t_token **tokens, char *str);
char	*handle_double_single_quotes(t_gc *gc, char *str);
int		define_token_type(char *str, int quote);
int		handle_unexpected_token(t_token *tokens);
int		handle_unclosed_quotes(char *str);
int		handle_herdocs(t_gc *gc, t_token *t_token, t_env *env);
int		handle_herdoc_input(t_gc *gc, char *str, t_token *token, t_env *env);
char	*handle_delemitre(t_gc *gc, char *str);
char	*handle_expand(t_gc *gc, char *str, t_env *env);
int		the_main_compute_lenght(t_gc *gc, char *str, int *i, t_env *env);
int		compute_expanded_length(t_gc *gc, char *str, t_env *env);
void	initial_struct_handle_expand(t_gc *gc, t_var_expand	**vx, int is_her);
void	the_main_expand(t_gc *gc, t_env *env, char *str, t_var_expand **vx);
int		check_quote_expand(char *str, int *is_squote, int *is_dquote);
char	*handle_expand_herdoc(t_gc *gc, char *str, int flag, t_env *env);
int		detect_quotes(char *str);
char	*get_varenv_value(char *var, t_env *env);
char	*handle_double_single_quotes(t_gc *gc, char *str);
void	build_command_list(t_gc *gc, t_token *tokens, t_command **cmd_list);
char	**get_inoutfile(t_gc *gc, t_token *tokens);
char	**get_commands(t_gc *gc, t_token *tokens);
int		get_herdoc_fd(t_token *tokens);
int		count_dollarsign_between_egall(char *str);
int		detect_dollar_sign_insquote(char *str);
void	call_main_signals(void);
void	call_herdoc_signals(void);
void	child_default_signal(void);
int		add_tokens_elemnt(t_gc *gc, char *str, t_token **tokens, t_env *env);
void	build_execute_cmds_list(t_gc *gc, t_token *tokens,
			t_command *cmds, t_env **ens);
int		the_main_work(t_main_var	*mv);
void	free_element_inside_while(t_main_var **mv);
void	free_element_in_end(t_main_var **mv);
void	clean_fd_herdoc(t_token *tokens);
void	initia_str_value(t_gc *gc, t_str_inputs **instr,
			char *str, char *export);
void	handle_expand_dollar_sign(t_gc *gc, t_token **tokens,
			t_env *env, char *str);
void	handle_expand_dollar_sign_export(t_gc *gc, t_token **tokens,
			t_env *env, t_str_inputs *ins);
void	handle_echo_expand_element(t_gc *gc, t_token **tokens, t_env *env,
			char *str);
int		detect_token_type_insquote(char *str);
int		detect_token_type_indolarsign(char *str);
int		count_words_expand(char const *str);
char	**ft_split_expand(t_gc *gc, char const *s);
int		detect_nombre_export_value(t_token *tmp);
int		compare_detect_condition(char *new_str);
char	*expand_split_first_var(t_gc *gc, char *str, t_env *env);
int		count_word_test(const char *s, char c);
void	fill_env_manual(t_main_var *mv);
int		initial_main_struct(t_main_var **mvar, char **env);
void	build_execute_cmds_list(t_gc *gc, t_token *tokens,
			t_command *cmds, t_env **ens);
int		max_herdoc_element(t_token *tokens);

#endif