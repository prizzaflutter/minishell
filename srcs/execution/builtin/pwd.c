#include "minishell.h"

void	my_pwd(t_env *env)
{
	char	content[4096];
	char	*cwd;

	cwd = getcwd(content, sizeof(content));
	if (cwd)
		printf("%s\n", content);
	else
	{
		while (env)
		{
			if (!ft_strcmp(env->key, "PWD"))
				printf("%s\n", env->value);
			env = env->next;
		}
	}
}
