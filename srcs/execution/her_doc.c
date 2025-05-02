// #include "minishell.h"

// int	handle_herdoc(int fd, char *line, t_command *cmd)
// {
// 	if (!ft_strncmp(line, cmd->inoutfile[1], ft_strlen(cmd->inoutfile[1]))
// 		&& line[ft_strlen(cmd->inoutfile[1])] == '\n')
// 		return (free(line), 0);
// 	ft_printf(0, "> ");
// 	write(fd, line, ft_strlen(line));
// 	free(line);
// 	return (1);
// }

// int	open_here_doc(int *fd1, int *fd2)
// {
// 	unlink("here_doc.txt");
// 	*fd1 = open("here_doc.txt", O_WRONLY
// 			| O_CREAT | O_TRUNC, 777);
// 	*fd2 = open("here_doc.txt", O_RDONLY);
// 	if (*fd1 < 0)
// 		return (0);
// 	if (*fd2 < 0)
// 		return (close(*fd1), 0);
// 	unlink("here_doc.txt");
// 	return (1);
// }

// int	handle_herdoc_infile(t_command *cmd)
// {
// 	char	*line;
// 	int		fd1;
// 	int		fd2;

// 	if (!open_here_doc(&fd1, &fd2))
// 		return (0);
// 	ft_printf(0, "> ");
// 	line = get_next_line(0);
// 	while (line)
// 	{
// 		if (!handle_herdoc(fd1, line, cmd))
// 			break ;
// 		line = get_next_line(0);
// 	}
// 	close (fd1);
// 	dup2(fd2, STDIN_FILENO);
// 	close(fd2);
// 	return (1);
// }