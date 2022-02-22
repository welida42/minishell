#include "../includes/minishell.h"

static void	print_error_exit1(char *argv)
{
	ft_putstr_fd("exit\nminishell: exit: ", 2);
	ft_putstr_fd(argv, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	exit(255);
}

static void	print_error_exit2(int exit_status)
{
	ft_putstr_fd("exit\n", 2);
	errno = exit_status;
	exit(exit_status);
}

void	exit_atoi(char *str)
{
	int	status;
	int	i;

	i = 0;
	if (str[0] == '-')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
		i++;
	if (str[i] || (str[0] == '-' && !str[1]))
		print_error_exit1(str);
	status = ft_atoi(str);
	exit (status);
}

int	ft_exit(t_param *prms, char **argv)
{
	int	i;
	int	size;

	size = size_env(argv);
	if (size == 1)
		exit(0);
	if (size == 2)
		exit_atoi(argv[1]);
	i = 0;
	if (argv[1][i] == '-')
		i++;
	while (argv[1][i] >= '0' && argv[1][i] <= '9')
		i++;
	if ((argv[1][i]) || (argv[1][0] == '-' && !argv[1][1]))
		print_error_exit1(argv[1]);
	else if (!argv[1][i] && size == 2)
		print_error_exit2(prms->exit_status);
	else if (!argv[1][i] && size > 2)
	{
		prms->exit_status = 1;
		ft_putstr_fd("exit\nminishell: exit: too many arguments\n", 2);
	}
	return (1);
}
