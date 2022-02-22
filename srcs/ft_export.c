#include "../includes/minishell.h"

int	add_to_exp(char ***env, char *var)
{
	char	**our_env;
	int		i;

	if (find_var_env(*env, var))
		return (0);
	i = size_env(*env) + 1;
	our_env = (char **) malloc((sizeof(char *) * (i + 1)));
	if (!our_env)
		return (1);
	i = 0;
	while ((*env)[i])
	{
		our_env[i] = (*env)[i];
		i++;
	}
	our_env[i] = ft_strdup(var);
	our_env[i + 1] = NULL;
	free(*env);
	*env = our_env;
	return (0);
}

void	print_export_err(char *argv, t_param *prms)
{
	prms->exit_status = 1;
	ft_putstr_fd("minishell: export: '", 2);
	ft_putstr_fd(argv, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
}

int	ft_export(char ***env, char **argv, t_param *prms)
{
	int		i;
	char	*p;

	if (env == NULL || *env == NULL)
		exit(1);
	if (!argv[1])
		return (print_exp(env));
	i = 1;
	while (argv[i])
	{
		if (ft_isalpha(argv[i][0]))
		{
			p = ft_strchr(argv[i], '=');
			if (p && (*(p - 1) != '+'))
				ft_setenv(env, argv[i]);
			else if (p && (*(p - 1) == '+'))
				concat_to_env(env, argv[i]);
			else if (p == NULL)
				add_to_exp(env, argv[i]);
		}
		else
			print_export_err(argv[i], prms);
		i++;
	}
	return (1);
}
