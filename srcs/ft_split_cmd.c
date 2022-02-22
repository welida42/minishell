#include "../includes/minishell.h"

void	ft_split_cmd_2(t_cmds	*tmp_cmd)
{
	int	i;

	i = 0;
	while (i < 32)
	{
		if (tmp_cmd->str[i][0] == '\0')
		{
			free(tmp_cmd->str[i]);
			tmp_cmd->str[i] = NULL;
		}
		i++;
	}
}

void	ft_split_cmd(t_info *info, t_param *prms)
{
	t_cmds	*tmp_cmd;
	t_cmds	*cur_cmd;
	int		i;

	cur_cmd = prms->lcmds;
	while (cur_cmd->prev)
		cur_cmd = cur_cmd->prev;
	prms->lcmds = cur_cmd;
	tmp_cmd = cur_cmd;
	info->cmd = cur_cmd;
	while (tmp_cmd->next)
	{
		i = 0;
		while (i < 32)
		{
			if (tmp_cmd->str[i][0] == '\0')
			{
				free(tmp_cmd->str[i]);
				tmp_cmd->str[i] = NULL;
			}
			i++;
		}
		tmp_cmd = tmp_cmd->next;
	}
	ft_split_cmd_2(tmp_cmd);
}
