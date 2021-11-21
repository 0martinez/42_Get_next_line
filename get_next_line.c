

#include "get_next_line.h"
/*
static int strlen(char *str1)
{
	int	i;

	i = 0;
	while()
}

static char *strjoin(char *line, char *str)
{
	int	i;

	i = 0;
}

*/
char *get_next_line(int fd)
{
	char *str;
	char *line;
	int	xd;
	int size;
	int aux;

	size = 1;
	xd = 1;
	aux = 0;
	str = malloc(sizeof(char) * 10 + 1);
	if (!str)
		return (0);
	//printf("%d", xd);
	while (xd == size)
	{
		xd = read(fd, str, size);
		//str[xd] = 0;
		//strjoin();
		aux += xd;
		printf("+%d+", xd);
	}
	printf("yy%dyy", aux);
	str[aux] = 0;
	return (str);
}

int main(void)
{
    int	fd;
	char *str;

	fd = open("LINES.txt", O_RDONLY);
	str = get_next_line(fd);
	printf("%s", str);
	free(str);
	close(fd);
	return (0);
}