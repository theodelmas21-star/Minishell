/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssivilay <ssivilay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 10:41:17 by ssivilay          #+#    #+#             */
/*   Updated: 2026/01/27 16:44:44 by ssivilay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	free_mem(char *buffer, char **stash, int fd)
{
	free(buffer);
	free(stash[fd]);
	stash[fd] = NULL;
}

void	add_to_stash(char **stash, int fd, char *buffer, ssize_t *read_bytes)
{
	char	*tmp;

	if (!stash[fd])
		stash[fd] = ft_strdup(buffer);
	else
	{
		tmp = stash[fd];
		stash[fd] = ft_strjoin(tmp, buffer);
		free(tmp);
	}
	while (stash[fd] && !ft_strchr(stash[fd], '\n') && *read_bytes > 0)
	{
		*read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (*read_bytes > 0)
		{
			buffer[*read_bytes] = '\0';
			tmp = stash[fd];
			stash[fd] = ft_strjoin(tmp, buffer);
			free(tmp);
		}
	}
}

char	*extract_line_bef_nl(char **stash, int fd)
{
	char	*tmp;
	char	*line;
	char	*new_stash;
	size_t	i;

	i = 0;
	while (stash[fd][i] && stash[fd][i] != '\n')
		i++;
	tmp = stash[fd];
	line = ft_substr(tmp, 0, i + 1);
	if (!line)
		return (NULL);
	new_stash = ft_substr(tmp, i + 1, ft_strlen(tmp) - (i + 1));
	free(tmp);
	stash[fd] = new_stash;
	if (!stash[fd] || stash[fd][0] == '\0')
	{
		free(stash[fd]);
		stash[fd] = NULL;
	}
	return (line);
}

char	*extract_last_line(char **stash, int fd)
{
	char	*extracted_line;

	extracted_line = ft_substr(stash[fd], 0, ft_strlen(stash[fd]));
	free(stash[fd]);
	stash[fd] = NULL;
	return (extracted_line);
}

char	*get_next_line(int fd)
{
	char		*buffer;
	static char	*stash[1024];
	ssize_t		read_bytes;

	if (fd < 0 || fd >= 1024 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	read_bytes = read(fd, buffer, BUFFER_SIZE);
	if (read_bytes == -1)
		return (free_mem(buffer, stash, fd), NULL);
	buffer[read_bytes] = '\0';
	add_to_stash(stash, fd, buffer, &read_bytes);
	free(buffer);
	if (stash[fd] && ft_strchr(stash[fd], '\n'))
		return (extract_line_bef_nl(stash, fd));
	if (stash[fd] && read_bytes == 0 && stash[fd][0] != '\0')
		return (extract_last_line(stash, fd));
	free(stash[fd]);
	stash[fd] = NULL;
	return (NULL);
}
