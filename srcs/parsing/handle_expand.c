/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_expand.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykassim <aykassim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 12:53:28 by aykassim          #+#    #+#             */
/*   Updated: 2025/04/25 10:58:50 by aykassim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int detect_quotes(char *str, int flag)
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
	{
		while (str[i])
    	{
    	    if (str[i] == '\'')
				return (1);
			i++;
    	}
	}
    return (0);
}

char *get_varenv_value(char *var, t_env *env)
{
	t_env	*current;

	current = env;
	while (current)
	{
		if (ft_strncmp(current->key, var, ft_strlen(var)) == 0)
			return (current->value);
		current = current->next;
	}
	return (NULL);
}

// char *ft_strjoin_char(char *s1, char c)
// {
// 	char	*res;
// 	int		i;

// 	if (!s1 || !c)
// 		return (NULL);
// 	res = malloc(sizeof(char) * (ft_strlen(s1) + 2));
// 	if (!res)
// 		return (NULL);
// 	i = 0;
// 	while (s1[i])
// 	{
// 		res[i] = s1[i];
// 		i++;
// 	}
// 	res[i] = c;
// 	res[i + 1] = '\0';
// 	return (res);
// }

int compute_expanded_length(t_gc *gc, char *str,int flag, t_env *env)
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
			if (str[i] && str[i] == '$')
				len++;
			else if (!ft_isalnum(str[i]) && str[i] != '?')
				len++;
			else if (str[i] == '?')
			{
				len += ft_strlen(ft_itoa(gc, exit_status(0, 0)));
				i++;
			}
			else if (str[i] == '$')
			{
				len++;
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

// int	handle_quotes(const char *str, int *i, int *in_single, int *in_double)
// {
// 	if (str[*i] == '"' && !(*in_single))
// 	{
// 		*in_double = !(*in_double);
// 		(*i)++;
// 		return (1);
// 	}
// 	else if (str[*i] == '\'' && !(*in_double))
// 	{
// 		*in_single = !(*in_single);
// 		(*i)++;
// 		return (1);
// 	}
// 	return (0);
// }

char *handle_expand_herdoc(t_gc *gc, char *str, int flag, t_env *env)
{
	char *res;
	char *env_tmp;
	char *new_str;
	int i;
	int j;
	int k;

	i = 0;
	j = 0;
	k = 0;
	if (!str)
		return (NULL);
	res = gc_malloc(gc, sizeof(char) * (compute_expanded_length(gc, str, flag, env) + 1), 0);
	if (!res)
		return (NULL);
	if (flag == 0)
	{
		while (str[i])
		{
			if (str[i] == '$')
			{
				i++;
				if (str[i] && str[i] == '$')
				{
					res[k++] = '@';
					i++;
				}
				else if (!ft_isalnum(str[i]) && str[i] != '?')
					res[k++] = '$';
				else if (str[i] == '?')
				{
					j = 0;
					char *nbr = ft_itoa(gc, exit_status(0, 0));
					while (nbr[j])
						res[k++] = nbr[j++];
					i++;
					j = 0;
				}
				else if (str[i] == '$')
					res[k++] = str[i++];
                else if (ft_isdigit(str[i]))
                    i++;
				else if (str[i] && (ft_isalpha(str[i]) || str[i] == '_'))
				{
					j = i;
					while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
						i++;
					env_tmp = ft_substr(gc, str, j, i - j);
					new_str = get_varenv_value(env_tmp, env);
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

char *handle_expand(t_gc *gc, char *str, t_env *env)
{
	char	*res;
	int		i;
	int		j;
	int		k;
	int		is_single_quote;
	int		is_double_quote;
	char	*env_tmp;
	char	*new_str;

	i = 0;
	k = 0;
	is_single_quote = 0;
	is_double_quote = 0;
	if (!str)
		return (NULL);
	res = gc_malloc(gc, sizeof(char) * (compute_expanded_length(gc, str, detect_quotes(str, 0), env) + 1), 0);
	if (!res)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '"' && !is_single_quote)
		{
			is_double_quote = !is_double_quote;
			i++;
		}
		else if (str[i] == '\'' && !is_double_quote)
		{
			is_single_quote = !is_single_quote;
			i++;
		}
		else if (str[i] == '$' && !is_single_quote)
		{
			i++;
			if (str[i] && str[i] == '$')
			{
				res[k++] = '@';
				i++;
			}
			else if (!ft_isalnum(str[i]) && str[i] != '?')
				res[k++] = '$';
			else if (str[i] == '?')
			{
				j = 0;
				char *nbr = ft_itoa(gc, exit_status(0, 0));
				while (nbr[j])
					res[k++] = nbr[j++];
				i++;
				j = 0;
			}
			else if (str[i] == '$')
				res[k++] = str[i++];
            else if (ft_isdigit(str[i]))
                i++;
			else if (str[i] && (ft_isalpha(str[i]) || str[i] == '_'))
			{
				j = i;
				while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
					i++;
				env_tmp = ft_substr(gc, str, j, i - j);
				new_str = get_varenv_value(env_tmp, env);
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
	res[k] = '\0';
	return (res);
}


// char *handle_expand_herdoc(char *str, int flag, t_env *env)
// {
// 	char *res = ft_strdup("");
// 	char *env_tmp;
// 	char *new_str;
// 	int i;
// 	int j;

// 	i = 0;
// 	j = 0;
// 	if (!str)
// 		return (NULL);
// 	// new_str = malloc(sizeof(char) * (compute_expanded_length(str, flag, env) + 1));
// 	if (flag == 0)
// 	{
// 		while (str[i] && str[i] != '$')
// 		{
// 			res = ft_strjoin_char(res, str[i]);
// 			i++;
// 		}
// 		if (str[i] == '$')
// 		{
// 			i++;
// 			j = i;
// 			while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
// 				i++;
// 			env_tmp = ft_substr(str, j, i - j);
// 			new_str = ft_strjoin(res, get_varenv_value(env_tmp, env));
// 			free(env_tmp);
// 			free(res);
// 			res = new_str;
// 		}
// 		while (str[i])
// 		{
// 			new_str = ft_strjoin_char(res, str[i]);
// 			free(res);
// 			i++;
// 			res = new_str;
// 		}
// 	} 
// 	else 
// 	{
// 		while (str[i])
// 		{
// 			new_str = ft_strjoin_char(res, str[i]);
// 			free(res);
// 			i++;
// 			res = new_str;
// 		}
// 	}
// 	return (res);
// }

// char *handle_expand_generic(char *str, t_env *env, int flag, int is_herdoc)
// {
// 	char	*res;
// 	int		i;
// 	int		j;
// 	int		k;
// 	int		is_single_quote;
// 	int		is_double_quote;
// 	char	*env_tmp;
// 	char	*new_str;

// 	i = 0;
// 	k = 0;
// 	is_single_quote = 0;
// 	is_double_quote = 0;
// 	if (!str)
// 		return (NULL);
// 	printf("count = %d\n", compute_expanded_length(str, flag, env));
// 	res = malloc(sizeof(char) * (compute_expanded_length(str, flag, env) + 1));
// 	if (!res)
// 		return (NULL);
// 	while (str[i])
// 	{
// 		if (!is_herdoc && handle_quotes(str, &i, &is_single_quote, &is_double_quote))
// 				continue;
// 		if (str[i] == '$' && (!is_single_quote || flag == 0))
// 		{
// 			i++;
// 			j = i;
// 			while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
// 				i++;
// 			env_tmp = ft_substr(str, j, i - j);
// 			new_str = get_varenv_value(env_tmp, env);
// 			j = 0;
// 			free(env_tmp);
// 			while (new_str && new_str[j])
// 			{
// 				res[k] = new_str[j];
// 				j++;
// 				k++;
// 			}
// 		}
// 		else
// 		{
// 			res[k] = str[i];
// 			k++;
// 			i++;
// 		}
// 	}
// 	return (res);
// }

