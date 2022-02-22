#include "../includes/minishell.h"

static int	ft_sort2(const char *s1, const char *s2)
{
	unsigned int	i;

	i = 0;
	if (s1 == s2)
		return (-1);
	while (s1[i] != '=' && s2[i] != '=' && s1[i] == s2[i])
		i++;
	if (s1[i] == '=' || s2[i] == '=')
		return (-1);
	else
		return (s1[i] - s2[i]);
}

void	sort_env(char **exp)
{
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	j = 1;
	if (exp[i])
	{
		while (exp[i + 1] != NULL)
		{
			if (ft_sort2(exp[i], exp[j]) > 0)
			{
				tmp = exp[j];
				exp[j] = exp[i];
				exp[i] = tmp;
				j = i;
			}
			else if (exp[j + 1] == NULL)
			{
				i++;
				j = i;
			}
			j++;
		}
	}
}

void	print_export(char **exp, int i, int j)
{
	while (exp[i])
	{
		if ((exp[i][0] == '_' && exp[i][1] == '='))
		{
			i++;
			continue ;
		}
		j = 0;
		write(1, "declare -x ", 11);
		while (exp[i][j] != '=' && exp[i][j])
			write(1, &exp[i][j++], 1);
		if (!exp[i][j])
		{
			write(1, "\n", 1);
			i++;
			continue ;
		}
		write(1, "=\"", 2);
		j += 1;
		while (exp[i][j])
			write(1, &exp[i][j++], 1);
		write(1, "\"\n", 2);
		i++;
	}
}

int	print_exp(char ***env)
{
	char	**exp;

	exp = copy_env(*env);
	sort_env(exp);
	print_export(exp, 0, 0);
	free_splitline(exp);
	return (1);
}
