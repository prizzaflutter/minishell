#include "minishell.h"

void	my_env(t_env *env)
{


	printf("the env is ================================================ : \n");
	while (env)
	{
		if (env->value)
			printf("%s=%s\n", env->key, env->value);
		else
			printf("%s\n", env->key);
		env = env->next;
	}
}
