/*
int handle_multiple_command(t_command *cmd, char **env)
{
	int fd[2];
	int prev_fd = -1;
	pid_t pid;
	t_command *current = cmd;

	while (current)
	{
		// Create a pipe for next command, if needed
		if (current->next)
		{
			if (pipe(fd) == -1)
			{
				perror("pipe");
				return 0;
			}
		}

		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			return 0;
		}

		if (pid == 0)
		{
			// If it's not the first command, set input from previous pipe
			if (prev_fd != -1)
			{
				dup2(prev_fd, STDIN_FILENO);
				close(prev_fd);
			}

			// If there is a next command, set output to current pipe
			if (current->next)
			{
				close(fd[0]);                 // close read end
				dup2(fd[1], STDOUT_FILENO);   // write to pipe
				close(fd[1]);
			}

			// Execute command
			execve(current->cmd[0], current->cmd, env);
			perror("execve failed");
			exit(1);
		}
		else
		{
			// Parent process: close used write end
			if (prev_fd != -1)
				close(prev_fd);

			// If there is a next command, keep read end for next loop
			if (current->next)
			{
				close(fd[1]);        // close write end
				prev_fd = fd[0];     // save read end
			}
		}

		current = current->next;
	}

	// Wait for all child processes
	while (wait(NULL) > 0);

	return 1;
}

*/