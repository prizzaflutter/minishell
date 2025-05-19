/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykassim <aykassim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 13:14:22 by aykassim          #+#    #+#             */
/*   Updated: 2025/05/15 21:01:16 by aykassim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*add_space_inputs(t_gc *gc, char *str)
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
	new_str = gc_malloc(gc, sizeof(char) * (len + cm * 2 + 1), 0);
	if (!new_str)
		return (printf ("Error alloc"), NULL);
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

int	its_have_dollar_signe(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

int	count_length_without_quotes(char *str)
{
	int		i;
	int		count;
	int		is_quote;
	char	quote_char;

	i = 0;
	count = 0;
	is_quote = 0;
	quote_char = 0;
	while (str[i])
	{
		if ((str[i] == '"' || str[i] == '\'') && !is_quote)
		{
			is_quote = 1;
			quote_char = str[i];
			i++;
			continue ;
		}
		else if (str[i] == quote_char && is_quote)
		{
			is_quote = 0;
			quote_char = 0;
			i++;
			continue ;
		}
		else if (is_quote)
			count++;
		else
			count++;
		i++;
	}
	return (count);
}

char	*handle_double_single_quotes(t_gc *gc, char *str)
{
	char	*new_str;
	int		is_quote;
	char	quote_char;
	int		i;
	int		j;

	i = 0;
	j = 0;
	is_quote = 0;
	quote_char = 0;
	new_str = gc_malloc(gc, sizeof(char)
			* (count_length_without_quotes(str) + 1), 0);
	if (!new_str)
		return (NULL);
	while (str[i])
	{
		if ((str[i] == '"' || str[i] == '\'') && !is_quote)
		{
			is_quote = 1;
			quote_char = str[i];
			i++;
			continue ;
		}
		else if (str[i] == quote_char && is_quote)
		{
			is_quote = 0;
			quote_char = 0;
			i++;
			continue ;
		}
		else if (is_quote)
			new_str[j++] = str[i++];
		else
			new_str[j++] = str[i++];
	}
	new_str[j] = '\0';
	return (new_str);
}

int	add_command_element(t_gc *gc, char *str, t_token **tokens, t_env *env)
{
	t_token	*new_token;
	char	**res;
	int		i;
	char	*new_str;
	t_token	*tmp;
	char	**char_tmp;
	t_token	*new_token_tmp;
	t_token	*tokens_tmp;

	tokens_tmp = NULL;
	if (!str || !tokens)
		return (1);
	str = add_space_inputs(gc, str);
	if (!str)
		return (printf("Error in add_space_inputs"), 1);
	res = ft_split(gc, str);
	if (!res)
		return (printf("Error in ft_split"), 1);
	i = 0;
	while (res[i])
	{
		new_token_tmp = ft_lstnew(gc, res[i], 4);
		if (!new_token_tmp)
			return (printf("Error in token creation"), 1);
		ft_lstadd_back(&tokens_tmp, new_token_tmp);
		i++;
	}
	tmp = tokens_tmp;
	while (tmp)
	{
		if (tmp->type == WORD)
		{
			if (tmp->prev && tmp->prev->type == HEREDOC && tmp->type == WORD)
			{
				new_token = ft_lstnew(gc, tmp->str, 1);
				if (!new_token)
					return (printf("Error in token creation new_token_tmp"), 1);
				ft_lstadd_back(tokens, new_token);
				tmp = tmp->next;
				continue ;
			}
			else if (its_have_dollar_signe(tmp->str))
			{
				new_str = handle_expand_generale(gc, tmp->str, detect_quotes(tmp->str, 0), env);
				if (!new_str)
					return (printf("Error in handle_expand"), 1);
				if (detect_quotes(new_str, 1) == 1)
				{
					new_str = handle_double_single_quotes(gc, new_str);
					if (!new_str)
						return (printf("Error in handle_double_single_quotes"), 1);
					new_token = ft_lstnew(gc, new_str, 1);
					ft_lstadd_back(tokens, new_token);
				}
				else
				{
					new_str = handle_double_single_quotes(gc, new_str);
					if (!new_str)
						return (printf("Error in handle_double_single_quotes"), 1);
					char_tmp = ft_split(gc, new_str);
					if (!char_tmp)
						return (printf("Error in ft_split tokens_tmp"), 1);
					i = 0;
					while (char_tmp[i])
					{
						printf("char tmp = %s\n",char_tmp[i]);
						new_token = ft_lstnew(gc, char_tmp[i], 1);
						if (!new_token)
							return (printf("Error in token creation new_token_tmp"), 1);
						ft_lstadd_back(tokens, new_token);
						i++;
					}
					tmp->str = handle_double_single_quotes(gc, new_str);
					if (!tmp->str)
						return (printf("Error in handle_double_single_quotes"), 1);
				}
			}
			else if (tmp->prev && ft_strcmp(tmp->prev->str, "echo") == 0)
			{
				tmp->str = handle_double_single_quotes(gc, tmp->str);
				if (!tmp->str)
					return (printf("Error in handle_double_single_quotes"), 1);
				new_token = ft_lstnew(gc, tmp->str, 1);
				ft_lstadd_back(tokens, new_token);
			}
			else
			{
				new_token = ft_lstnew(gc, tmp->str, 1);
				ft_lstadd_back(tokens, new_token);
			}
		}
		else
		{
			new_token = ft_lstnew(gc, tmp->str, 1);
			if (!tmp->str)
				return (printf("Error in handle_double_single_quotes"), 1);
			ft_lstadd_back(tokens, new_token);
		}
		tmp = tmp->next;
	}
	gc_clear(gc, 4);
	tokens_tmp = NULL;
	return (0);
}
