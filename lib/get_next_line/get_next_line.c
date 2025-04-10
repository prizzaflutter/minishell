/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaskour <iaskour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 16:03:56 by iaskour           #+#    #+#             */
/*   Updated: 2025/03/07 17:08:53 by iaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	find_new_line(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

static char	*configure_line(char *line)
{
	char	*new_remainder;
	ssize_t	i;

	i = 0;
	while (line[i] != '\n' && line[i] != '\0')
		i++;
	if (line[i] == 0 || line[1] == 0)
		return (NULL);
	new_remainder = ft_substr(line, i + 1, ft_strlen(line) - i);
	if (*new_remainder == 0)
	{
		free(new_remainder);
		new_remainder = NULL;
	}
	line[i + 1] = 0;
	return (new_remainder);
}

static char	*get_line(int fd, char *remainder, char *buffer)
{
	ssize_t		bytes_read;
	char		*tmp_remainder;

	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(remainder);
			return (NULL);
		}
		else if (bytes_read == 0)
			break ;
		buffer[bytes_read] = 0;
		if (!remainder)
			remainder = ft_strdup("");
		tmp_remainder = remainder;
		remainder = ft_strjoin(tmp_remainder, buffer);
		free(tmp_remainder);
		tmp_remainder = NULL;
		if (find_new_line(buffer) != -1)
			break ;
	}
	return (remainder);
}

char	*get_next_line(int fd)
{
	static char	*remainder;
	char		*line;
	char		*buffer;

	buffer = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		free(remainder);
		free(buffer);
		remainder = NULL;
		buffer = NULL;
		return (NULL);
	}
	buffer = (char *)malloc((size_t)(BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	line = get_line(fd, remainder, buffer);
	free(buffer);
	buffer = NULL;
	if (!line)
		return (NULL);
	remainder = configure_line(line);
	return (line);
}
