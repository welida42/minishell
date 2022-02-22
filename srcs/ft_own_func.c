/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_own_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtawney <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 15:15:30 by dtawney           #+#    #+#             */
/*   Updated: 2021/05/23 15:15:37 by dtawney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_own_func(t_param *prms, char **argv, t_cmds *cmd)
{
	if (ft_strcmp(argv[0], "env") == 0)
		return (ft_env(prms->envp));
	else if (ft_strcmp(argv[0], "export") == 0)
		return (ft_export(&prms->envp, argv, prms));
	else if (ft_strcmp(argv[0], "echo") == 0)
		return (ft_echo(cmd->cmd, argv));
	else if (ft_strcmp(argv[0], "unset") == 0)
		return (ft_unset(&prms->envp, argv, prms));
	else if (ft_strcmp(argv[0], "cd") == 0)
		return (ft_cd(argv[1], &prms->envp, prms));
	else if (ft_strcmp(argv[0], "pwd") == 0)
		return (ft_pwd());
	else if (ft_strcmp(argv[0], "exit") == 0)
		return (ft_exit(prms, argv));
	return (0);
}
