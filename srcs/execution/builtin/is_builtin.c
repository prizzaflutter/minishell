#include "minishell.h"

char *is_builtin (char *cmd)
{
	if (ft_strncmp(cmd, "echo", 4) == 0)
		return ("echo");
	else if (ft_strncmp(cmd, "cd", 2) == 0)
		return ("cd");
	else if (ft_strncmp(cmd, "pwd", 3) == 0)
		return ("pwd");
	else if (ft_strncmp(cmd, "export", 6) == 0)
		return ("export");
	else if (ft_strncmp(cmd, "unset", 5) == 0)
		return ("unset");
	else if (ft_strncmp(cmd, "env", 3) == 0)
		return ("env");
	else if (ft_strncmp(cmd, "exit", 4) == 0)
		return ("exit");
	else
		return (NULL);
}
