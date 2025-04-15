#include "minishell.h"

void my_unset(char **argv)
{
	printf("my_unset called with argument: %s\n", argv[1]);
	if (unsetenv(argv[1]) == -1)
	{
		perror("unsetenv");
		return;
	}
}
