/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_mem.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtawney <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/13 18:23:37 by dtawney           #+#    #+#             */
/*   Updated: 2021/06/13 18:23:41 by dtawney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_cmds	*ft_free_cur_lcmd(t_cmds *cur_lcmd, int i)
{
	t_cmds	*tmp_lcmd;

	if (cur_lcmd->cmd)
		free(cur_lcmd->cmd);
	if (cur_lcmd->str)
	{
		while (cur_lcmd->str[i] && i < 32)
		{
			free(cur_lcmd->str[i]);
			i++;
		}
		free(cur_lcmd->str);
	}
	tmp_lcmd = cur_lcmd;
	free(tmp_lcmd);
	return (cur_lcmd->next);
}

void	ft_free_lcmds(t_param *prms)
{
	t_cmds	*cur_lcmd;

	cur_lcmd = prms->lcmds;
	if (cur_lcmd)
		while (cur_lcmd->prev)
			cur_lcmd = cur_lcmd->prev;
	while (cur_lcmd)
		cur_lcmd = ft_free_cur_lcmd(cur_lcmd, 0);
	prms->lcmds = NULL;
}
