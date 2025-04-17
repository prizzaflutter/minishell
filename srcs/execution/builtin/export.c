#include "minishell.h"

char **split_key_value(char *str)
{
	char **result;
	char *equal_pos;

	equal_pos = strchr(str, '=');
	if (!equal_pos)
		return NULL;
	result = malloc(sizeof(char *) * 3);
	if (!result)
		return NULL;
	result[0] = strndup(str, equal_pos - str);
	result[1] = strdup(equal_pos + 1);
	result[2] = NULL;
	return result;
}

int is_valid_identifier(const char *str)
{
	if (!str || !*str)
		return 0;
	if (!ft_isalpha(*str) && *str != '_')
		return 0;
	while (*str)
	{
		if (!ft_isalnum(*str) && *str != '_')
			return 0;
		str++;
	}
	return 1;
}

void	my_export(t_env **env, char **cmd_args)
{
	int i = 1;
	if (!cmd_args[1])
	{
		t_env *current = *env;
		while (current)
		{
			if (!current->value || ft_strcmp(current->value, "") == 0)
			{
				printf("declare -x %s\n", current->key);
			}
			else
				printf("declare -x %s=\"%s\"\n", current->key, current->value);

			current = current->next;
		}
		return;
	}
	while(cmd_args[i])
	{
		char **key_value = split_key_value(cmd_args[i]);
		char *key;
		char *value;
		if (key_value)
		{
			key = key_value[0];
			value = key_value[1];
		}
		else
		{
			key = strdup(cmd_args[i]);
			value = NULL;
		}
		if (!is_valid_identifier(key))
		{
			printf("export: `%s%s`: not a valid identifier\n", key, value);
			free(key);
			if (value) free(value);
			if (key_value) free(key_value);
			i++;
			continue;
		}
		t_env *current = *env;
		t_env *found = NULL;
		while (current)
		{
			if (strcmp(current->key, key) == 0)
			{
				found = current;
				break;
			}
			current = current->next;
		}
		if(found)
		{
			if (value)
			{
				free(found->value);
				found->value = strdup(value);
			}
			found->is_exported = true;
			free(key);
			if (value) free(value);
			if (key_value) free(key_value);
		}
		else
		{
			t_env *new_env = malloc(sizeof(t_env));
			if (!new_env)
			{
				printf("Error: Memory allocation failed\n");
				free(key);
				if (value) free(value);
				if (key_value) free(key_value);
				i++;
				continue;
			}
			new_env->key = key;
			new_env->value = value ? strdup(value) : strdup("");
			new_env->is_exported = true;
			new_env->next = NULL;

			if (!*env)
				*env = new_env;
			else
			{
				t_env *last = *env;
				while (last->next)
					last = last->next;
				last->next = new_env;
			}
			if (key_value)
			{
				free(key_value);
			}
		}
		i++;
	}
}
