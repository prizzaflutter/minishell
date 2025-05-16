#include "minishell.h"


int add_tokens_elemnt(t_gc *gc,char *str, t_token **tokens, t_env *env)
{
	int fd;

	fd = -2;
	if (handle_unclosed_quotes(str))
		return (exit_status(1, 2), -1);
	if (add_command_element(gc, str, tokens, env))
	{
		printf("Error in add_command_element\n");
		return (-1);
	}
	if (handle_unexpected_token(*tokens))
		return (exit_status(1, 2), -1);
	fd = handle_herdocs(gc, *tokens, env);
	if (fd == -1)
		return (-1);
	return (fd);
}









////awesui handleeeeeeee
// minishell:</>export x="a  b  c"
// minishell:</>export c=$x
// minishell:</>


int main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	t_gc *gc = malloc(sizeof(t_gc));
	if (!gc)
		return (1);
	gc->head = NULL;
	t_env		*env_struct;
	t_token		*tokens;
	t_command	*cmds;
	char		*input;
	int			fd;

	tokens = NULL;
	env_struct = fill_env(gc, env);
	input = NULL;
	cmds = NULL;
	fd = -1;
	call_signals();
	while (1)
	{
		input = readline("minishell:</>");
		if (!input)
			break;
		if (ft_is_only_whitespace(input))
		{
			free(input);
			continue;
		}
		if (*input)
			add_history(input);
		fd = add_tokens_elemnt(gc, input, &tokens, env_struct);
		if (fd == -1)
		{
			printf("here\n");
			gc_clear(gc, 1);
			tokens = NULL;
			free(input);
			continue ;
		}
		if(tokens)
		{
			build_command_list(gc, tokens, &cmds);
			print_command_list(cmds);
			execute_command(gc, cmds, env_struct);
		}
		gc_clear(gc, 1);
		gc_clear(gc, 3);
		tokens = NULL;
		cmds = NULL;
		free(input);
	}
	gc_clear(gc, 1);
	gc_clear(gc, 0);
	free(gc);
	return (0);
}
