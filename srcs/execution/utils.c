#include "minishell.h"

char **convert_env_to_array(t_gc *gc, t_env *env)
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
	env_array = gc_malloc(gc, sizeof(char *) * (size + 1));
	if (!env_array)
		return (NULL);
	env_array[size] = NULL;
	while (env)
	{
		char *tmp = gc_strcat(gc, env->key, "=");
		env_array[i] = gc_strcat(gc, tmp, env->value);
		if (!env_array[i])
			return NULL;
		i++;
		env = env->next;
	}
	return (env_array);
}
