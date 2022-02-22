#include "../includes/minishell.h"

void	ft_echo_n(char *str)
{
	str += 4;
	if (*str == ' ')
		str++;
	str += 2;
	if (*str == ' ')
		str++;
	ft_putstr_fd(str, 1);
}

int	ft_echo(char *str, char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
		i++;
	if (i == 1)
	{
		ft_putstr_fd("\n", 1);
		return (1);
	}
	if ((!ft_strcmp(argv[1], "-n")))
		ft_echo_n(str);
	else
	{
		str += 4;
		if (*str == ' ')
			str++;
		ft_putstr_fd(str, 1);
		ft_putstr_fd("\n", 1);
	}
	return (1);
}
