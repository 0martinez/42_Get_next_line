

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
	printf("%d", i);
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
	static char *line;
	int	xd;
	int aux;

	xd = BUFFER_SIZE;
	aux = 0;
	str = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!str)
		return (0);
	while (xd > 0)
	{
		xd = read(fd, str, BUFFER_SIZE);
		str[xd] = 0;
		//printf("|%s|", str);
		line = ft_strjoin(line, str);
		//free(str);
		aux += xd;
		//printf("+%d+", xd);
	}
	//xd = read(fd, str, BUFFER_SIZE);
	//str[xd] = 0;
	line[aux] = 0;
	//ls = xd;
	return (line);
}

int main(void)
{
    int	fd;
	int xd = 0;
	char *str;
	fd = open("LINES.txt", O_RDONLY);
	printf("//%d//", BUFFER_SIZE);
	str = get_next_line(fd);
	while(str != 0)
	{
		printf("-%s-", str);
		free(str);
		str = get_next_line(fd);
	}
	//str = get_next_line(fd);
	//printf("-%s-", str);
	free(str);
	close(fd);
	return (0);
}