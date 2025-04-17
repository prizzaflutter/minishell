#include "minishell.h"

t_env *fill_env (char **envp)
{
	t_env *head = NULL;
	t_env *current = NULL;
	int i = 0;

	while (envp[i])
	{
		char *equal_pos = strchr(envp[i], '=');
		if (!equal_pos)
		{
			i++;
			continue;
		}
		size_t key_len = equal_pos - envp[i];
		t_env *new_node = malloc(sizeof(t_env));
		if (!new_node)
			return NULL;
		new_node->key = strndup(envp[i], key_len);
		new_node->value = strdup(equal_pos + 1);
		new_node->next = NULL;
		if (!head)
			head = new_node;
		else
			current->next = new_node;
		current = new_node;
		i++;
	}
	return head;
}

// void fill_env(t_env *env, char **envp)
// {
// 	int i = 0;
// 	while(envp[i])
// 	{
// 		char *equal_pos = strchr(envp[i], '=');
// 		if (!equal_pos)
// 		{
// 			 i++;
// 			 continue; 
// 		}
// 		size_t key_len = equal_pos - envp[i];
// 		env[i].key = strndup(envp[i], key_len);
// 		env[i].value = strdup(equal_pos + 1);
// 		env[i].next = NULL;
// 		if (i > 0)
// 			env[i - 1].next = &env[i];
// 		i++;
// 	}
// }