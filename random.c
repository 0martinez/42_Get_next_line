#include <stdio.h>
#include <stdlib.h>

static char	*teesting(char *str)
{
	char	*aux;

	aux = malloc (4 + 1);
	aux[0] = '4';
	aux[1] = '3';
	aux[2] = '2';
	aux[3] = '1';
	aux[4] = 0;
	free(str);
	return (aux);
}

void leaks()
{
	system("leaks -q a.out");
}

static void	to_be_free(char *str)
{
	str = malloc (5);
	str[0] = '1';
	str[1] = '2';
	str[2] = '3';
	str[3] = '4';
	str[4] = 0;
}

int	main(void)
{
	static char	*str;

	atexit(leaks);
	if (!str)
	{
		printf("a");
	}
	to_be_free(str);
	printf("------%s-----", str);
	if (str)
	{
		printf("lol");
	}
	str = malloc (sizeof(char) * 4 + 1);
	if (str)
	{
		printf("b");
	}
	str[0] = '1';
	str[1] = '2';
	str[2] = '3';
	str[3] = '4';
	str[4] = 0;
	printf("\n%s\n", str);
	str = teesting(str);
	printf("\n%s\n", str);
	if (str[0] == 0)
		printf("c");
	free(str);
	printf("\n%s\n", str);
	if (str[0] == 0)
		printf("d");
	printf("%s", str);
	//str = to_be_free(str);
	if (str[0] == 0)
		printf("e");
	return (0);
}
