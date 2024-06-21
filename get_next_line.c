/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niarygin <niarygin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 13:51:43 by niarygin          #+#    #+#             */
/*   Updated: 2024/06/21 16:20:31 by niarygin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*line_alloc(int fd, char *line_buf)
{
	char		*read_buf;
	ssize_t		bytes_num;

	read_buf = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!read_buf)
		return (mem_free(&line_buf));
	bytes_num = 1;
	while (!ft_strchr(line_buf, '\n') && bytes_num > 0)
	{
		bytes_num = read(fd, read_buf, BUFFER_SIZE);
		if (bytes_num == -1)
		{
			free(read_buf);
			read_buf = NULL;
			return (mem_free(&line_buf));
		}
		read_buf[bytes_num] = '\0';
		line_buf = ft_strjoin(line_buf, read_buf);
		if (!line_buf)
			break ;
	}
	free(read_buf);
	read_buf = NULL;
	return (line_buf);
}

static char	*return_line(char *line_buf)
{
	char			*line;
	unsigned int	i;

	i = 0;
	if (!line_buf[i])
		return (NULL);
	while (line_buf[i] && line_buf[i++] != '\n')
		;
	line = (char *)malloc((i + 1) * sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (line_buf[i] && line_buf[i] != '\n')
	{
		line[i] = line_buf[i];
		i++;
	}
	if (line_buf[i] == '\n')
	{
		line[i] = line_buf[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

static char	*go_to_next_line(char *line_buf)
{
	char	*new_line;
	int		i;
	int		j;

	i = 0;
	while (line_buf[i] && line_buf[i] != '\n')
		i++;
	if (!line_buf[i])
		return (mem_free(&line_buf));
	new_line = (char *)malloc((ft_strlen(line_buf) - i + 1) * sizeof(char));
	if (!new_line)
		return (mem_free(&line_buf));
	j = 0;
	i++;
	while (line_buf[i])
		new_line[j++] = line_buf[i++];
	new_line[j] = '\0';
	free(line_buf);
	line_buf = NULL;
	return (new_line);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*line_buf;

	if (fd < 0 || BUFFER_SIZE < 1 || BUFFER_SIZE > INT_MAX)
		return (NULL);
	line_buf = line_alloc(fd, line_buf);
	if (!line_buf)
		return (NULL);
	line = return_line(line_buf);
	if (!line)
		return (mem_free(&line_buf));
	line_buf = go_to_next_line(line_buf);
	return (line);
}
