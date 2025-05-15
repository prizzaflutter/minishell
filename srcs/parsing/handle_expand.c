/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_expand.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykassim <aykassim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 12:53:28 by aykassim          #+#    #+#             */
/*   Updated: 2025/05/15 17:10:13 by aykassim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	dollar_sign_position(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			return (i);
		i++;
	}
	return (-1);
}

int	detetect_varenv_quotes(char *str)
{
	int		i;
	int		pos;
	int		in_single_quote;
	int		in_double_quote;

	i = 0;
	pos = dollar_sign_position(str);
	in_single_quote = 0;
	in_double_quote = 0;
	while (str[i] && i < pos)
	{
		if (str[i] == '\'' && !in_double_quote)
			in_single_quote = !in_single_quote;
		else if (str[i] == '"' && !in_single_quote)
			in_double_quote = !in_double_quote;
		i++;
	}
	if (in_single_quote)
		return (1);
	return (0);
}

int	detect_quotes(char *str, int flag)
{
	int		i;

	i = 0;
	if (flag == 1)
	{
		while (str[i])
		{
			if (str[i] == '"' || str[i] == '\'')
				return (1);
			i++;
		}
	}
	else
		return (detetect_varenv_quotes(str));
	return (0);
}

char	*get_varenv_value(char *var, t_env *env)
{
	t_env	*current;

	current = env;
	while (current)
	{
		if (ft_strcmp(current->key, var) == 0)
			return (current->value);
		current = current->next;
	}
	return (NULL);
}

int	compute_expanded_length(t_gc *gc, char *str, int flag, t_env *env)
{
	int		i;
	int		j;
	int		len;
	char	*varname;
	char	*varvalue;

	i = 0;
	len = 0;
	while (str[i])
	{
		if (str[i] == '$' && flag == 0)
		{
			i++;
			if (!str[i])
			{
				len++;
				break ;
			}
			if (str[i] == '$')
			{
				len++;
				i++;
			}
			else if (str[i] == '?')
			{
				len += ft_strlen(ft_itoa(gc, exit_status(0, 0)));
				i++;
			}
			else if (str[i] && (ft_isalpha(str[i]) || str[i] == '_'))
			{
				j = i;
				while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
					i++;
				varname = ft_substr(gc, str, j, i - j);
				varvalue = get_varenv_value(varname, env);
				if (varvalue)
					len += ft_strlen(varvalue);
			}
			else
			{
				len++;
				i++;
			}
		}
		else
		{
			len++;
			i++;
		}
	}
	return (len);
}

char	*handle_expand_generale(t_gc *gc, char *str, int flag, t_env *env)
{
	char	*res;
	char	*env_tmp;
	char	*new_str;
	char	*nbr;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = 0;
	if (!str)
		return (NULL);
	res = gc_malloc(gc, sizeof(char)
			* (compute_expanded_length(gc, str, flag, env) + 1), 0);
	if (!res)
		return (NULL);
	if (flag == 0)
	{
		while (str[i])
		{
			if (str[i] == '$')
			{
				i++;
				if (!str[i])
				{
					res[k++] = '$';
					break ;
				}
				else if (str[i] && str[i] == '$')
				{
					res[k++] = '$';
					i++;
				}
				else if (str[i] == '?')
				{
					j = 0;
					nbr = ft_itoa(gc, exit_status(0, 0));
					while (nbr[j])
						res[k++] = nbr[j++];
					i++;
					j = 0;
				}
				else if (ft_isdigit(str[i]) || str[i] == '@')
					i++;
				else if (str[i] && (ft_isalpha(str[i]) || str[i] == '_'))
				{
					j = i;
					while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
						i++;
					env_tmp = ft_substr(gc, str, j, i - j);
					new_str = get_varenv_value(env_tmp, env);
					if (!new_str)
						new_str = gc_strdup(gc, "");
					new_str = handle_double_single_quotes(gc, new_str);
					j = 0;
					while (new_str && new_str[j])
						res[k++] = new_str[j++];
				}
				else
					res[k++] = str[i++];
			}
			else
				res[k++] = str[i++];
		}
	}
	else
	{
		while (str[i])
			res[k++] = str[i++];
	}
	res[k] = '\0';
	return (res);
}
