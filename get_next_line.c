/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omartine <omartine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 17:35:34 by omartine          #+#    #+#             */
/*   Updated: 2021/12/09 19:55:55 by omartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_line_return(char *container, int jump)
{
	int		i;
	char	*line_return;

	i = 0;
	line_return = malloc(sizeof(char) * jump + 1);
	if (!line_return)
		return (0);
	line_return[jump] = 0;
	while (i < jump)
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

	i = ft_strlen(container);
	j = 0;
	new_container = malloc(sizeof(char) * (i - jump) + 1);
	if (!new_container)
		return (0);
	new_container[i - jump] = 0;
	while (jump <= i)
	{
		new_container[j] = container[jump];
		j++;
		jump++;
	}
	free(container);
	return (new_container);
}

static char	*ft_line(char *container)
{
	int		jump;
	char	*line_return;

	if (check_container(container) != 0)
	{
		jump = check_container(container);
		line_return = ft_line_return(container, jump);
		return (line_return);
	}
	line_return = line_no_jump(container);
	return (line_return);
}

static char	*ft_container(char *container)
{
	int		jump;

	if (check_container(container) != 0)
	{
		jump = check_container(container);
		container = new_container(container, jump);
		return (container);
	}
	free(container);
	return (0);
}

char	*get_next_line(int fd)
{
	int			bites;
	char		*line_return;
	char		*str;
	static char	*container;

	str = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!container)
		container = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!str || BUFFER_SIZE <= 0 || !container)
		return (0);
	while (check_container(container) == 0)
	{
		bites = read(fd, str, BUFFER_SIZE);
		if (bites <= 0)
			break ;
		str[bites] = 0;
		container = ft_strjoin(container, str);
	}
	free(str);
	line_return = ft_line(container);
	container = ft_container(container);
	return (line_return);
}
/*
void leaks()
{
	system("leaks -q a.out");
}*/
/*
int	main(void)
{
	int		fd;
	char	*str;

	//atexit(leaks);
	fd = open("./testgnl/files/41_no_nl", O_RDONLY);
	str = get_next_line(fd);
	while (str != 0)
	{
		printf("++%s++", str);
		free(str);
		str = get_next_line(fd);
	}
	free(str);
	close(fd);
	//system("leaks -q a.out");
	return (0);
}*/
