#include "../includes/minishell.h"

char	**copy_env(char **env)
{
	char	**our_env;
	int		i;

	if (env == NULL || *env == NULL)
		return (NULL);
	i = size_env(env);
	our_env = (char **)malloc((sizeof(char *) * (i + 1)));
	if (!our_env)
		return (NULL);
	i = 0;
	while (env[i])
	{
		our_env[i] = ft_strdup(env[i]);
		i++;
	}
	our_env[i] = NULL;
	return (our_env);
}

int	replace_value_env(char **env, char *key, char *value)
{
	int		i;
	int		len_key;
	char	*tmp;

	if (env == NULL || *env == NULL || key == NULL || value == NULL)
		return (1);
	len_key = ft_strlen(key);
	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], key, len_key) && env[i][len_key] == '=')
		{
			free(env[i]);
			tmp = ft_strjoin(key, "=");
			env[i] = ft_strjoin(tmp, value);
			free(tmp);
			return (0);
		}
		i++;
	}
	return (1);
}

int	add_to_env(char ***env, char *var)
{
	char	**our_env;
	int		i;

	if (env == NULL || *env == NULL || var == NULL)
		return (1);
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

int	ft_setenv(char ***env, char *var)
{
	char	*key;
	char	*value;

	if (env == NULL || *env == NULL || var == NULL)
		return (1);
	key = ft_get_key(var);
	value = ft_get_value(var);
	if (find_var_env(*env, key))
		del_from_env(env, key);
	add_to_env(env, var);
	free(key);
	free(value);
	return (0);
}
