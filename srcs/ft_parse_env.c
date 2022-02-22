/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 13:51:03 by student           #+#    #+#             */
/*   Updated: 2021/05/16 13:51:35 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_search_lstat(t_param *prms, char *str, int k)
{
	struct stat		buf;

	if (lstat(str, &buf) == 0)
	{
		k = -1;
		while (str[++k])
			prms->argv0[k] = str[k];
		prms->argv0[k] = '\0';
		return (1);
	}
	return (0);
}

int	ft_search_cmd2(t_param *prms, char *str, int i, int y)
{
	int				k;

	while (prms->prm_res[i])
	{
		y = 0;
		ft_erase_str(str);
		while (prms->prm_res[i] != ':' && prms->prm_res[i])
			str[y++] = prms->prm_res[i++];
		if (i > 0 && str[y - 1] != '/')
			str[y++] = '/';
		k = 0;
		while (prms->argv0[k])
			str[y++] = prms->argv0[k++];
		str[y] = '\0';
		if (ft_search_lstat(prms, str, -1) == 1)
			return (1);
		i++;
	}
	return (0);
}

void	ft_relative_path(t_param *prms, int res)
{
	char	*tmp;
	char	*tmp2;

	tmp = getcwd(NULL, 0);
	tmp2 = ft_strjoin(tmp, "/");
	free(tmp);
	tmp = ft_strjoin(tmp2, prms->argv0);
	free(tmp2);
	res = 0;
	while (tmp[res])
	{
		prms->argv0[res] = tmp[res];
		res++;
	}
	prms->argv0[res] = '\0';
	free(tmp);
}

void	ft_search_cmd(t_param *prms, t_cmds *cmd, int i)
{
	char			str[BUFFER_SIZE];
	int				res;

	ft_erase_str(prms->argv0);
	while (cmd->cmd[i] != '\0' && !ft_isspace(cmd->cmd[i]))
	{
		prms->argv0[i] = cmd->cmd[i];
		i++;
	}
	prms->argv0[i] = '\0';
	res = 0;
	if (prms->argv0[0] == '.' && prms->argv0[1] == '.')
		ft_relative_path(prms, 0);
	else if (!(prms->argv0[0] == '/' || (prms->argv0[0] == '.'
				&& prms->argv0[1] == '/')))
	{
		if (ft_search_cmd2(prms, str, 0, 0) == 0)
			prms->exit_status = 127;
	}
}
