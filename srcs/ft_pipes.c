#include "../includes/minishell.h"

int	pipe_handler(t_param *prms, t_info *info, t_cmds *cmd, t_cmds *tmp_cmd)
{
	pipe(info->pipe_fd);
	info->pid = fork();
	if (info->pid == 0)
	{
		close(info->pipe_fd[0]);
		info->output = info->pipe_fd[1];
		dup2(info->output, 1);
		close(info->pipe_fd[1]);
		if (tmp_cmd && info->error_num == 0)
			ft_exec_cmd2(prms, tmp_cmd);
		else
			ft_exec_cmd2(prms, cmd);
		exit(0);
	}
	wait(&prms->exit_status);
	close(info->pipe_fd[1]);
	info->input = info->pipe_fd[0];
	dup2(info->input, 0);
	close(info->pipe_fd[0]);
	info->cmd = info->cmd->next;
	return (0);
}

int	info_init(t_info *info)
{
	info->error_num = 0;
	info->input = 0;
	info->output = 1;
	info->classic_in = dup(0);
	info->classic_out = dup(1);
	return (0);
}

int	check_last_char(t_info *info, t_param *prms)
{
	info->tmp_cmd = prms->lcmds;
	if (info->tmp_cmd->flag == '2' && info->tmp_cmd->str[0] == NULL)
		return (2);
	while (info->tmp_cmd->next)
		info->tmp_cmd = info->tmp_cmd->next;
	if ((info->tmp_cmd->flag == '|' || info->tmp_cmd->flag == '>' ||\
			info->tmp_cmd->flag == 'd' || info->tmp_cmd->flag == '<' ||\
			info->tmp_cmd->flag == '2') && info->tmp_cmd->str[0] == NULL)
	{
		prms->exit_status = 258;
		ft_putstr_fd("minishell: syntax error near unexpected token ", 2);
		if (info->tmp_cmd->prev)
		{
			if (info->tmp_cmd->prev->flag == '|')
				ft_putstr_fd("'|'", 2);
			else
				ft_putstr_fd("'newline'", 2);
		}
		ft_putstr_fd("\n", 2);
		return (1);
	}
	return (0);
}

void	ft_finish_init(t_info *info, t_param *prms)
{
	prms->exit_status %= 255;
	info->input = 0;
	info->error_num = 0;
	dup2(info->classic_in, 0);
	dup2(info->classic_out, 1);
}

int	ft_pipes(t_param *prms)
{
	t_info	info;

	ft_split_cmd(&info, prms);
	info_init(&info);
	if (check_last_char(&info, prms))
		return (1);
	info.tmp_cmd = NULL;
	term_init3(*prms);
	while (info.cmd)
	{
		while (info.cmd && info.cmd->flag == '|' && info.input >= 0)
			pipe_handler(prms, &info, info.cmd, info.tmp_cmd);
		info.tmp_cmd = info.cmd;
		redir_handler(&info, prms);
		if (back_redir_handler(&info))
			continue ;
		ft_exec_cmd1(&info, prms);
		ft_finish_init(&info, prms);
		info.cmd = info.cmd->next;
	}
	term_init2(*prms);
	return (0);
}
