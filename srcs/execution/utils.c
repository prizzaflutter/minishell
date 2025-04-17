#include "minishell.h"

char **convert_env_to_array(t_env *env)
{
	int		i;
	int		size;
	char	**env_array;
	t_env	*temp;

	i = 0;
	size = 0;
	env_array = NULL;
	if (!env)
		return (NULL);
	temp = env;
	while (temp)
	{
		size++;
		temp = temp->next;
	}
	env_array = malloc(sizeof(char *) * (size + 1));
	if (!env_array)
		return (NULL);
	env_array[size] = NULL;
	while (env)
	{
		env_array[i] = malloc(strlen(env->key) + strlen(env->value) + 2);
		if (!env_array[i])
			return NULL;
		strcpy(env_array[i], env->key);
		strcat(env_array[i], "=");
		strcat(env_array[i], env->value);
		i++;
		env = env->next;
	}
	return (env_array);
}
