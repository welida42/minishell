#include "../includes/minishell.h"

int	del_from_env(char ***env, char *key)
{
	char	**our_env;
	int		i;
	int		size;
	int		flag;
	char	*p;

	size = size_env(*env);
	our_env = (char **) malloc(sizeof(char *) * size);
	if (!our_env)
		return (-1);
	i = 0;
	flag = 0;
	p = find_var_env(*env, key);
	while (i < size)
	{
		if (p == (*env)[i])
			flag = 1;
		our_env[i] = (*env)[i + flag];
		i++;
	}
	free(p);
	our_env[i] = NULL;
	free(*env);
	*env = our_env;
	return (0);
}

int	ft_unset(char ***env, char **argv, t_param *prms)
{
	int	i;

	prms->exit_status = 0;
	if (env == NULL || *env == NULL || argv == NULL)
		exit(1);
	i = 1;
	while (argv[i])
	{
		if (ft_isalpha(argv[i][0]) && find_var_env(*env, argv[i]))
			del_from_env(env, argv[i]);
		else if (ft_isalpha(argv[i][0]) && !find_var_env(*env, argv[i]))
		{
			i++;
			continue ;
		}
		else
		{
			prms->exit_status = 1;
			ft_putstr_fd("minishell: unset: '", 2);
			ft_putstr_fd(argv[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
		}
		i++;
	}
	return (1);
}
