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

void	my_export(t_env **env, char **cmd_args)
{
	char **key_value = split_key_value(cmd_args[1]);
	printf("the cmd args in export is : %s\n", cmd_args[1]);
	printf("key_value[0] is : %s\n", key_value[0]);
	printf("key_value[1] is : %s\n", key_value[1]);

	if (!key_value)
	{
		printf("Error: Invalid argument for export\n");
		return;
	}
	t_env *new_env = malloc(sizeof(t_env));
	if (!new_env)
	{ 
		printf("Error: Memory allocation failed\n");
		free(key_value[0]);
		free(key_value[1]);
		free(key_value);
		return;
	}
	new_env->key = key_value[0];
	new_env->value = key_value[1];
	new_env->next = NULL;

	printf("the env is : %s\n", new_env->key);
	printf("the env value is : %s\n", new_env->value);
	if (!*env)
	{
		printf("the env is null\n");
		*env = new_env;
	}
	else
	{
		printf("the env is not null\n");
		t_env *current = *env;
		while (current->next)
			current = current->next;
		current->next = new_env;
	}
	t_env *current = *env;
	while (current)
	{
		printf("Key : %s\n", current->key);
		printf("Value : %s\n", current->value);
		current = current->next;
	}
}
