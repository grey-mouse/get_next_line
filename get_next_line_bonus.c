#include "get_next_line_bonus.h"

static char	*line_alloc(int fd, char *line_buf)
{
	char		*read_buf;
	ssize_t		bytes_num;

	read_buf = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!read_buf)
		return (free(line_buf), NULL);
	bytes_num = 1;
	while (!ft_strchr(line_buf, '\n') && bytes_num > 0)
	{
		bytes_num = read(fd, read_buf, BUFFER_SIZE);
		if (bytes_num == -1)
		{
			free(read_buf);
			free(line_buf);
			return (NULL);
		}
		read_buf[bytes_num] = '\0';
		line_buf = ft_strjoin(line_buf, read_buf);
		if (!line_buf)
			break;
	}
	free(read_buf);
	return (line_buf);
}

static char	*return_line(char *line_buf)
{
	char	*line;
	int		i;

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
	char	*new_line_buf;
	int		i;
	int		j;

	i = 0;
	while (line_buf[i] && line_buf[i] != '\n')
		i++;
	if (!line_buf[i])
	{
		free(line_buf);
		return (NULL);
	}
	new_line_buf = (char *)malloc((ft_strlen(line_buf) - i + 1) * sizeof(char));
	if (!new_line_buf)
	{
		free(line_buf);
		line_buf = NULL;
		return (NULL);
	}
	j = 0;
	i++;
	while (line_buf[i])
		new_line_buf[j++] = line_buf[i++];
	new_line_buf[j] = '\0';
	free(line_buf);
	return (new_line_buf);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*line_buf[1024];

	if (fd < 0 || fd > 1024 || BUFFER_SIZE < 1 || BUFFER_SIZE > INT_MAX)
		return (NULL);
	line_buf[fd] = line_alloc(fd, line_buf[fd]);
	if (!line_buf[fd])
		return (NULL);
	line = return_line(line_buf[fd]);
	if (!line)
	{
		free(line_buf[fd]);
		line_buf[fd] = NULL;
		return (NULL);
	}
	line_buf[fd] = go_to_next_line(line_buf[fd]);
	return (line);
}