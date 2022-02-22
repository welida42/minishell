#include "../includes/minishell.h"

int	replace_pwd(char ***env, char *oldpwd)
{
	char	*tmp;
	char	*path;

	path = getcwd(NULL, 0);
	replace_value_env(*env, "PWD", path);
	tmp = ft_strjoin("OLDPWD=", oldpwd);
	if (!find_var_env(*env, "OLDPWD"))
		ft_setenv(env, tmp);
	else
		replace_value_env(*env, "OLDPWD", oldpwd);
	free(path);
	free(tmp);
	return (0);
}

void static	error_cd(t_param *prms)
{
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd("\n", 2);
	prms->exit_status = 1;
}

int	ft_cd(char *str, char ***env, t_param *prms)
{
	char	*path;
	char	*oldpwd;

	path = NULL;
	if (str == NULL || (!ft_strcmp(str, "--")))
		path = ft_getenv(*env, "HOME");
	else if (!ft_strcmp(str, "-"))
	{
		path = ft_getenv(*env, "OLDPWD");
		if (path == NULL)
			path = ft_getenv(*env, "HOME");
	}
	else
		path = str;
	oldpwd = getcwd(NULL, 0);
	if (path == NULL)
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
	else if ((chdir(path)))
		error_cd(prms);
	else
		replace_pwd(env, oldpwd);
	free(oldpwd);
	return (1);
}
