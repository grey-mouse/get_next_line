#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

// Main function to test get_next_line() function.
//gcc -Wall -Werror -Wextra get_next_line.c get_next_line_utils.c main.c
//gcc -Wall -Werror -Wextra -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c

//to test multiple descriptors
//gcc -Wall -Werror -Wextra get_next_line_bonus.c get_next_line_utils_bonus.c main.c
//gcc -Wall -Werror -Wextra -D BUFFER_SIZE=42 get_next_line_bonus.c get_next_line_utils_bonus.c main.c

char	*get_next_line(int fd);

int	main(void)
{
	int		fd;
	//int	fd1, fd2;
	char	*line;
	int		count;
	//int		count1, count2;

	count = 0;
	fd = open("several_nl.txt", O_RDONLY);
	//fd = open("example.txt", O_RDONLY);
	//fd = open("empty.txt", O_RDONLY);
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

	// To check stdin run program as follows: ./a.out < example.txt
	/*printf("\nTest for STDIN\n");
	count = 0;
	while (1)
	{
		line = get_next_line(STDIN_FILENO);
		if (line == NULL)
			break;
		count++;
		printf("[%d]:%s\n", count, line);
		free(line);
		line = NULL;
	}*/

	//To check several file descriptors
	/*printf("TEST: check several file descriptors\n");
	fd1 = open("example.txt", O_RDONLY);
	if (fd1 == -1)
	{
		printf("Error opening file");
		close(fd1);
		return (1);
	}

	fd2 = open("example2.txt", O_RDONLY);
	if (fd2 == -1)
	{
		printf("Error opening file");
		close(fd2);
		return (1);
	}
	count1 = 0;
	count2 = 0;
	while (1)
	{
		line = get_next_line(fd1);
		if (line == NULL)
			break;
		count1++;
		printf("[%d]:%s\n", count1, line);
		free(line);
		line = NULL;
		line = get_next_line(fd2);
		if (line == NULL)
			break;
		count2++;
		printf("[%d]:%s\n", count2, line);
		free(line);
		line = NULL;
	}
	close(fd1);
	close(fd2);*/

	return (0);
}

//empty file
//new line only in file
//no new line in file (buf 42, 41, 43)
//several nl in file (buf 42, 41, 43)
//start with nl 
//big file with nl
//big file without nl
//wrong fd
//read from stdin
//multiple fd
//multiple fd when one is incorrect
