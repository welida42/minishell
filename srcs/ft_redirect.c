#include "../includes/minishell.h"

int	back_redir_handler(t_info *info)
{
	if (info->tmp_cmd->flag == '<' && info->cmd->flag == '|' &&\
		info->tmp_cmd->next->flag != '>' && info->tmp_cmd->next->flag != 'd')
	{
		if (info->input < 0)
		{
			info->input = 0;
			dup2(info->classic_in, 0);
			dup2(info->classic_out, 1);
			info->cmd = info->cmd->next;
			info->error_num = 1;
			return (1);
		}
		info->str = copy_env(info->tmp_cmd->str);
		free_splitline(info->cmd->str);
		info->cmd->str = info->str;
		return (2);
	}
	return (0);
}

int	redir_err(char *filename, t_param *prms)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(filename, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	prms->exit_status = 1;
	return (1);
}

char	*get_name(t_cmds *cmd)
{
	char	*filename;

	filename = NULL;
	if (cmd->next)
		filename = cmd->next->str[0];
	return (filename);
}

int	selector_redir(t_info *info, t_cmds *cmd, t_param *prms)
{
	char	*filename;

	filename = get_name(cmd);
	if (cmd->flag == '>')
	{
		info->output = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (info->output < 0)
			return (redir_err(filename, prms));
		dup2(info->output, 1);
	}
	else if (cmd->flag == 'd')
	{
		info->output = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (info->output < 0)
			return (redir_err(filename, prms));
		dup2(info->output, 1);
	}
	else if (cmd->flag == '<')
	{
		info->input = open(filename, O_RDONLY);
		if (info->input < 0)
			return (redir_err(filename, prms));
		dup2(info->input, 0);
	}
	return (0);
}

void	redir_handler(t_info *info, t_param *prms)
{
	while (info->cmd->flag == '>' || info->cmd->flag == 'd' ||\
		info->cmd->flag == '<')
	{
		selector_redir(info, info->cmd, prms);
		if (info->cmd->next)
			info->cmd = info->cmd->next;
		else
			return ;
	}
}
