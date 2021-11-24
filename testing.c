/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omartine <omartine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 17:35:34 by omartine          #+#    #+#             */
/*   Updated: 2021/11/24 21:00:10 by omartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

static int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i] != 0)
		i++;
	return (i);
}

static char	*ft_strjoin(char *container, char *str)
{
	char	*new_container;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (container[0] != 0)
		i = ft_strlen(container);
	i += ft_strlen(str);
	//printf("++lengt value: %d++", i);
	new_container = (char *) malloc(sizeof(char) * i + 1);
	new_container[i] = 0;
	i = 0;
	if (container[0] != 0)
	{
		while (container[i] != 0)
		{
			new_container[i] = container[i];
			i++;
		}
	}
	while (str[j] != 0)
	{
		new_container[i] = str[j];
		i++;
		j++;
	}
	//printf("|container value prefree: %s|\n", container);
	free(container);
	return (new_container);
}

static int	check_container(char *container)
{
	int	i;

	i = 0;
	while (container[i] != 0)
	{
		if (container[i] == '\n')
			return (i + 1);
		i++;
	}
	return (0);
}

static char	*ft_line_return(char *container, int jump)
{
	int		i;
	int		j;
	char	*line_return;

	i = 0;
	line_return = malloc(sizeof(char) * jump + 1);
	if (!line_return)
		return (0);
	line_return[jump] = 0;
	while (line_return[i] != 0)
	{
		line_return[i] = container[i];
		i++;
	}
	return (line_return);
}

static char	*new_container(char *container, int jump)
{
	char	*new_container;
	int		i;
	int		j;

	//printf("++%s++", container);
	i = ft_strlen(container);
	printf("!!!!%d-%d!!!!", i, jump);
	j = 0;
	new_container = malloc(sizeof(char) * (i - jump) + 1);
	if (!new_container)
		return (0);
	printf("HOLA");
	new_container[i - jump] = 0;
	while (jump < i)
	{
		new_container[j] = container[jump];
		j++;
		jump++;
	}
	//printf("|container value prefree: %s|\n", container);
	free(container);
	return (new_container);
}

static char	*get_next_line(int fd)
{
	int			i;
	int			jump;
	int			bites;
	char		*line_return;
	char		*str;
	static char	*container;

	bites = BUFFER_SIZE;
	jump = 0;
	str = malloc(sizeof(char) * BUFFER_SIZE + 1);
	//printf("random :%s++", container);
	if (!container)
		container = malloc(sizeof(char) * BUFFER_SIZE + 1);
	//printf("random :%s--", container);
	if (!str || !container)
		return (0);
	while (bites > 0 && check_container(container) == 0)
	{
		bites = read(fd, str, BUFFER_SIZE);
		str[bites] = 0;
		container = ft_strjoin(container, str);
	}
	if (bites == 0)
		return (0);
	if (check_container(container) != 0)
	{
		jump = check_container(container);
		//printf("|jump value: %d|\n", jump);
		line_return = ft_line_return(container, jump);
		//printf("|line return: %s|\n", line_return);
		container = new_container(container, jump);
		//printf("|new container: %s|\n", container);
		return (line_return);
	}
	//return (container);
	return (0);
}

int main(void)
{
	int		fd;
	int		xd = 0;
	char	*str;

	fd = open("LINES", O_RDONLY);
	str = get_next_line(fd);
	while (str != 0)
	{
		printf("|-%s-|", str);
		free(str);
		str = get_next_line(fd);
	}
	/*if (str[0] == 0)
		printf("aa");*/
	return (0);
}
