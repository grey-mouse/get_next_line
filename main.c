#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

// Main function to test get_next_line() function.
//gcc -Wall -Werror -Wextra get_next_line.c get_next_line_utils.c main.c
//gcc -Wall -Werror -Wextra -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c

char	*get_next_line(int fd);

int	main(void)
{
	int		fd;
	char	*line;
	int		count;

	count = 0;
	fd = open("example.txt", O_RDONLY);
	if (fd == -1)
	{
		printf("Error opening file");
		return (1);
	}
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break;
		count++;
		printf("[%d]:%s\n", count, line);
		free(line);
		line = NULL;
	}
	close(fd);
	return (0);
}