/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 17:20:36 by student           #+#    #+#             */
/*   Updated: 2021/05/05 17:21:18 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_find_err(int	errnum)
{
	if (errnum == 13)
		return (126);
	else if (errnum == 2)
		return (127);
	return (2);
}

static void	print_err_127(char **argv)
{
	write(2, "minishell: ", 11);
	write(2, argv[0], ft_strlen(argv[0]));
	write(2, ": command not found\n", 20);
}

static void	print_err(char **argv, t_param *prms)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(argv[0], 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd("\n", 2);
	prms->exit_status = ft_find_err(errno);
	exit (prms->exit_status);
}

void	ft_exec_cmd2(t_param *prms, t_cmds *cmd)
{
	char	**argv;
	int		nerror;

	argv = cmd->str;
	prms->exit_status = 0;
	if (ft_own_func(prms, argv, cmd))
		return ;
	if (prms->lcmds->str[0] == NULL)
		exit(0);
	prms->prm_res = find_var_env(prms->envp, "PATH");
	ft_search_cmd(prms, cmd, 0);
	argv[0] = prms->argv0;
	if (prms->exit_status == 127)
		print_err_127(argv);
	else
	{
		signal(SIGINT, NULL);
		signal(SIGILL, NULL);
		nerror = execve(argv[0], argv, prms->envp);
		if (nerror != 0)
			print_err(&argv[0], prms);
	}
}

void	ft_exec_cmd1(t_info *info, t_param *prms)
{
	if (is_our_ft(info->tmp_cmd->str[0]))
		ft_exec_cmd2(prms, info->tmp_cmd);
	else
	{
		info->n_fork = fork();
		if (info->n_fork == 0)
		{
			if (info->input >= 0)
				ft_exec_cmd2(prms, info->tmp_cmd);
			exit(prms->exit_status);
		}
		wait(&prms->exit_status);
	}
}
