/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omartine <omartine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 18:51:57 by omartine          #+#    #+#             */
/*   Updated: 2021/11/24 17:34:41 by omartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while(str[i] != 0)
		i++;
	return (0);
}

static char	*ft_strjoin(char *last, char *str)
{
	int		i;
	char	*line;
	int		j;

	i = 0;
	if (!last)
	{
	}
	else
		i = ft_strlen(last);
	i += ft_strlen(str);
	printf("%d", i);
	j = 0;
	line = (char *) malloc(sizeof(char) * i + 1);
	if (!line)
		return (0);
	line[i] = 0;
	i = 0;
	while (last[i] != 0)
	{
		line[i] = last[i];
		i++;
	}
	while (str[j] != 0 && str[j] != '\n')
	{
		line[i] = str[j];
		i++;
		j++;
	}
	return (line);
}

static int	check_container(const char *line)
{
	int	i;

	i = 0;
	while (line[i] != 0)
	{
		if (line[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

static char	*ft_return(int i, const char *line)
{
	static int		j;
	char			*str;

	j = 0;
	str = malloc(sizeof(char) * i + 1);
	while (j < i)
	{
		str[j] = line[j];
		j++;
	}
	str[j] = 0;
	j++;
	return (str);
}

static char	*ft_adeblas(const char *line)
{
	static int		i;

	i = 0;
	while (line[i] != '\n')
		i++;
	i++;
	return (ft_return(i - 1, line));
}

char	*get_next_line(int fd)
{
	char		*str;
	static char	*line;
	int			xd;
	int			aux;

	xd = BUFFER_SIZE;
	aux = 0;
	//ft_str para retornar el trozo de tu container y le asignas un nuevo valor sin tu str
	/*if (check_container(line) == 1)
		return (ft_adeblas(line));*/
	str = malloc(sizeof(char) * BUFFER_SIZE + 1);
	line = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!str)
		return (0);
	while (xd > 0 && check_container(line) != 1)
	{
		xd = read(fd, str, BUFFER_SIZE);
		str[xd] = 0;
		line = ft_strjoin(line, str);
	}
	if (check_container(line) == 1)
	{
		return (ft_adeblas(line));
	}
	free(str);
	return (0);
}

int main(void)
{
	int		fd;
	int		xd = 0;
	char	*str;

	printf("holla");
	fd = open("LINES", O_RDONLY);
	str = get_next_line(fd);
	/*while (str != 0)
	{
		printf("-%s-", str);
		free(str);
		str = get_next_line(fd);
	}*/
	free(str);
	close(fd);
	return (0);
}
