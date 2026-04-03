/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssivilay <ssivilay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 10:44:47 by tdelmas2          #+#    #+#             */
/*   Updated: 2026/04/03 15:01:54 by ssivilay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	free_str(char **str)
{
	int	i;

	i = 0;
	while (i < 1024)
	{
		free(str[i]);
		str[i] = NULL;
		i++;
	}
}

char	*get_next_line(int fd)
{
	static char	*str[1024];
	char		*buffer;
	char		*new_line;
	int			bits;
	char		*temp;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > 1023)
		return (free_str(str), NULL);
	buffer = malloc(BUFFER_SIZE + 1);
	if (buffer == NULL)
		return (NULL);
	while (checker(str[fd]) == 0)
	{
		bits = read(fd, buffer, BUFFER_SIZE);
		if (bits < 0)
			return (free(buffer), NULL);
		if (bits == 0)
			break ;
		buffer[bits] = 0;
		str[fd] = ft_strjoin(str[fd], buffer);
	}
	new_line = get_line(str[fd]);
	temp = str[fd];
	str[fd] = get_next(str[fd]);
	return (free(buffer), free(temp), new_line);
}

/*int	main(void)
{
	int fd;
	char *l1;
	char *l2;
	char *l3;
	fd = open("infile", O_RDONLY);

	l1 = get_next_line(fd);
	l2 = get_next_line(fd);
	l3 = get_next_line(fd);
	printf("%s\n", l1);
	printf("%s\n", l2);
	printf("%s\n", l3);
	free(l1);
	free(l2);
	free(l3);
	return (0);
}*/