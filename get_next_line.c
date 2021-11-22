

#include "get_next_line.h"

static int ft_strlen(char *str)
{
	int	i;

	i = 0;
	while(str[i] != 0)
		i++;
	return (0);
}

static char *ft_strjoin(char *last, char *str)
{
	int	i;
	char *line;
	int	j;

	i = ft_strlen(last);
	i += ft_strlen(str);
	j = 0;
	line = (char *) malloc(sizeof(char) * i + 1);
	if (!line)
		return (0);
	line[i] = 0;
	i = 0;
	while(last[i] != 0)
	{
		line[i] = last[i];
		i++;
	}
	while(str[j] != 0 && str[j] != '\n')
	{
		line[i] = str[j];
		i++;
		j++;
	}
	return (line);
}

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
		str[xd] = 0;
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
	while
	str = get_next_line(fd);
	printf("%s", str);
	free(str);
	close(fd);
	return (0);
}