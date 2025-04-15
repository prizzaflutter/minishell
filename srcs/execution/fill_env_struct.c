#include "minishell.h"

int env_size (char **env)
{
	int i = 0;
	while(env[i])
		i++;
	return i;
}

void fill_env(t_env *env, char **envp)
{
	int i = 0;
	while(envp[i])
	{
		char *equal_pos = strchr(envp[i], '=');
		if (!equal_pos)
		{
			 i++;
			 continue; 
		}
		size_t key_len = equal_pos - envp[i];
		env[i].key = strndup(envp[i], key_len);
		env[i].value = strdup(equal_pos + 1);
		env[i].next = NULL;
		if (i > 0)
			env[i - 1].next = &env[i];
		i++;
	}
}