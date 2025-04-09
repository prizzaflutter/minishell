#include "minishell.h"

void my_echo(char **argv)
{
	int i = 0;
	int new_line = 0;
	if (argv[1] && ft_strncmp(argv[1], "-n", 2) == 0)
	{
		new_line = 1;
		i++;
	}
	while (argv[i])
	{
		printf("%s", argv[i]);
		if (argv[i + 1])
			printf(" ");
		i++;
	}
	if (new_line == 1)
		printf("\n");
}