#include "../includes/minishell.h"

int	concat_1(char ***env, char *key, char *value, int i)
{
	char	*p;

	p = ft_strjoin((*env)[i], value);
	free((*env)[i]);
	free(value);
	free(key);
	(*env)[i] = p;
	return (0);
}

int	concat_2(char ***env, char *key, char *value, int i)
{
	char	*p;

	p = ft_strjoin((*env)[i], "=");
	free((*env)[i]);
	free(key);
	key = ft_strjoin(p, value);
	(*env)[i] = key;
	free(p);
	free(value);
	return (0);
}

int	concat(char ***env, char *key, char *value, char *p)
{
	int	i;

	i = 0;
	while (p && (*env)[i])
	{
		if (p == (*env)[i] && ft_strchr((*env)[i], '='))
			return (concat_1(env, key, value, i));
		else if ((p == (*env)[i]) && (ft_strchr((*env)[i], '=') == NULL))
			return (concat_2(env, key, value, i));
		i++;
	}
	return (1);
}

int	concat_to_env(char ***env, char *var)
{
	char	*p;
	char	*key;
	char	*value;
	int		i;

	i = 0;
	while (var[i] != '+')
		i++;
	key = ft_substr(var, 0, i);
	value = ft_get_value(var);
	p = find_var_env(*env, key);
	if (!concat(env, key, value, p))
		return (0);
	p = ft_strjoin(key, "=");
	free(key);
	key = ft_strjoin(p, value);
	add_to_env(env, key);
	free(key);
	free(value);
	free(p);
	return (0);
}
