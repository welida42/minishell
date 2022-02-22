#include "../includes/minishell.h"

int	size_env(char **env)
{
	int	i;

	if (env == NULL || *env == NULL)
		return (0);
	i = 0;
	while (env[i])
		i++;
	return (i);
}

char	*find_var_env(char **env, char *key)
{
	int		i;
	char	*env_key;

	if (env == NULL || *env == NULL || key == NULL)
		return (NULL);
	i = 0;
	while (env[i])
	{
		env_key = ft_get_key(env[i]);
		if (!ft_strcmp(env_key, key))
		{
			free(env_key);
			return (env[i]);
		}
		free(env_key);
		i++;
	}
	return (NULL);
}

char	*ft_getenv(char **env, char *key)
{
	int	i;
	int	j;

	if (env == NULL || *env == NULL || key == NULL)
		return (NULL);
	i = 0;
	j = ft_strlen(key);
	while (env[i])
	{
		if (!ft_strncmp(env[i], key, j) && env[i][j] == '=')
			return (env[i] + j + 1);
		i++;
	}
	return (NULL);
}

char	*ft_get_value(char *var)
{
	int		i;
	char	*value;

	if (!var)
		return (NULL);
	i = 0;
	while (var[i] != '=' && var[i])
		i++;
	if (!var[i])
		return (NULL);
	i++;
	value = ft_substr(var, i, ft_strlen(var) - i);
	return (value);
}

char	*ft_get_key(char *var)
{
	int		i;
	char	*key;

	if (!var)
		return (NULL);
	i = 0;
	while (var[i] != '=' && var[i] && var[i] != '+')
		i++;
	key = ft_substr(var, 0, i);
	return (key);
}
