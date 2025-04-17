#include "minishell.h"

char	*add_space_inputs(char *str)
{
	int		i;
	int		j;
	int		len;
	int		cm;
	char	*new_str;
	int		is_quote;
	char	quote_char;

	i = 0;
	j = 0;
	cm = 0;
	is_quote = 0;
	quote_char = 0;
	len = ft_strlen(str);
	while (str[i])
	{
		if ((str[i] == '"' || str[i] == '\'') && !is_quote)
		{
			is_quote = 1;
			quote_char = str[i];
		}
		else if (str[i] == quote_char && is_quote)
		{
			is_quote = 0;
			quote_char = 0;
		}
		else if (!is_quote)
		{
			if ((str[i] == '<' && str[i + 1] == '<')
				|| (str[i] == '>' && str[i + 1] == '>'))
			{
				cm++;
				i++;
			}
			else if (str[i] == '|' || str[i] == '>' || str[i] == '<')
				cm++;
		}
		i++;
	}
	new_str = malloc(sizeof(char) * (len + cm * 2 + 1));
	if (!new_str)
		return(printf ("Error alloc"), NULL);
	i = 0;
	j = 0;
	is_quote = 0;
	quote_char = 0;
	while (str[i])
	{
		if ((str[i] == '"' || str[i] == '\'') && !is_quote)
		{
			is_quote = 1;
			quote_char = str[i];
			new_str[j++] = str[i++];
		}
		else if (str[i] == quote_char && is_quote)
		{
			is_quote = 0;
			quote_char = 0;
			new_str[j++] = str[i++];
		}
		else if ((str[i] == '>' && str[i + 1] == '>') && !is_quote)
		{
			new_str[j++] = ' ';
			new_str[j++] = str[i++];
			new_str[j++] = str[i++];
			new_str[j++] = ' ';
		}
		else if ((str[i] == '<' && str[i + 1] == '<') && !is_quote)
		{
			new_str[j++] = ' ';
			new_str[j++] = str[i++];
			new_str[j++] = str[i++];
			new_str[j++] = ' ';
		}
		else if ((str[i] == '|' || str[i] == '>' || str[i] == '<') && !is_quote)
		{
			new_str[j++] = ' ';
			new_str[j++] = str[i++];
			new_str[j++] = ' ';
		}
		else
			new_str[j++] = str[i++];
	}
	new_str[j] = '\0';
	return (new_str);
}

int define_token_type(char *str)
{
	if (ft_strcmp(str, "|") == 0)
		return (PIPE);
	else if (ft_strcmp(str, "<") == 0)
		return (REDIR_IN);
	else if (strcmp(str, ">") == 0)
		return (REDIR_OUT);
	else if (ft_strcmp(str, "<<") == 0)
		return (HEREDOC);
	else if (ft_strcmp(str, ">>") == 0)
		return (APPEND);
	else
		return (WORD);
}

int its_have_dollar_signe(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

int add_command_element(char *str, t_token **tokens, t_env *env)
{
	t_token	*new_token;
	char	**res;
	int i;
	char	*new_str;
	t_token	*tmp;

	if (!str || !tokens)
		return (1);
	str = add_space_inputs(str);
	if (!str)
		return (printf("Error in add_space_inputs"), 1);
	res = ft_split(str, ' ');
	if (!res)
		return (printf("Error in ft_split"), 1);
	i = 0;
	while (res[i])
	{
		new_token = ft_lstnew(res[i]);
		if (!new_token)
			return (printf("Error in token creation"), free(res), 1);
		ft_lstadd_back(tokens, new_token);
		i++;
	}
	tmp = *tokens;
	while (tmp)
	{
		if (tmp->type == WORD)
		{
			if (its_have_dollar_signe(tmp->str))
			{
				new_str = handle_expand(tmp->str, env);
				if (!new_str)
					return (printf("Error in handle_expand"), free(res), 1);
				free(tmp->str);
				tmp->str = new_str;
			}
		}
		tmp = tmp->next;
	}
	free(res);
	return (0);
}
