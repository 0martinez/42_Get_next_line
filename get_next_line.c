/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omartine <omartine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 17:35:34 by omartine          #+#    #+#             */
/*   Updated: 2021/12/02 20:06:27 by omartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
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
	if (!str)
		return (0);
	if (container[0] != 0)
		i = ft_strlen(container);
	i += ft_strlen(str);
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
	free(container);
	return (new_container);
}

static int	check_container(char *container)
{
	int	i;

	i = 0;
	if (container[0] == 0)
		return (0);
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

static char	*adeblas(char *str)
{
	int		i;
	char	*to_return;

	if (str[0] == 0)
		return (0);
	i = 0;
	i = ft_strlen(str);
	to_return = malloc(sizeof(char) * i + 1);
	if (!to_return)
		return (0);
	to_return[i] = 0;
	i = 0;
	while (str[i] != 0)
	{
		to_return[i] = str[i];
		i++;
	}
	return (to_return);
}

static char	*to_be_free(char *str)
{
	free(str);
	return (0);
}

char	*get_next_line(int fd)
{
	int			jump;
	int			bites;
	char		*line_return;
	char		*str;
	static char	*container;

	/*if (!fd)
		return (0);*/
	bites = 1;
	jump = 0;
	str = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!container)
	{
		container = malloc(sizeof(char) * BUFFER_SIZE + 1);
		//printf("\nRESERVA MALLOC CONTAINER\n");
	}
	if (!str || !container)
	{
		//printf("a");
		return (0);
	}
	while ((bites > 0 && check_container(container) == 0))
	{
		bites = read(fd, str, BUFFER_SIZE);
		//printf("\n%d\n", bites);
		/*if (bites == 0)
		{
			if (container[0] == 0)
			{
				printf("\na\n");
				return (0);
			}
			str = adeblas(container);
			free(container);
			return (str);
		}*/
		if (bites <= 0)
		{
			//printf("\nbites 0\n");
			break ;
		}
		str[bites] = 0;
		container = ft_strjoin(container, str);
	}
	free(str);
	//printf("\nFLG\n");
	if (container[0] == 0)
	{
		//printf("\nCONTAINER[0]==0\n");
		free(container);
		return (0);
	}
	//printf("\nFLG2\n");
	if (check_container(container) != 0)
	{
		jump = check_container(container);
		line_return = ft_line_return(container, jump);
		container = new_container(container, jump);
		return (line_return);
	}
	//printf("\nFLG3\n");
	line_return = adeblas(container);
	container = to_be_free(container);
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
