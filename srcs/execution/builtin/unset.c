#include "minishell.h"

void my_unset(t_env **env, char **argv)
{
	if (!argv || !*argv)
		return;
	int i = 1;
	while(argv[i])
	{
		printf("unset: %s\n", argv[i]);
		if (!is_valid_identifier(argv[i]))
		{
			printf("unset: `%s`: not a valid identifier\n", argv[i]);
			i++;
			continue;
		}

		t_env *current = *env;
		t_env *prev = NULL;
		
		while (current)
		{
			t_env *next = current->next;
			if (strcmp(current->key, argv[i]) == 0)
			{
				printf("found the key : %s\n", current->key);
				if (prev)
					prev->next = next;
				else
					*env = next;
				if (current->key)
					free(current->key);
				if (current->value)
					free(current->value);
				free(current);
				break ;
			}
			else
				prev = current;
			current = next;
		}
		i++;
	}
}
