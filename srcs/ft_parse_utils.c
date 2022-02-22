/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtawney <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 14:16:35 by dtawney           #+#    #+#             */
/*   Updated: 2021/06/05 14:16:38 by dtawney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_cmds	*ft_malloc_lcmd(t_param *prms)
{
	int		i;
	int		y;
	t_cmds	*new;

	i = 0;
	new = (t_cmds *)malloc(sizeof(t_cmds));
	new->cmd = (char *)malloc(sizeof(char) * (300));
	while (i < 300)
		new->cmd[i++] = '\0';
	new->next = NULL;
	new->str = (char **)malloc(sizeof(char *) * 32);
	i = 0;
	while (i < 32)
	{
		new->str[i] = (char *)malloc(sizeof(char) * BUFFER_SIZE);
		y = 0;
		while (y < BUFFER_SIZE)
			new->str[i][y++] = '\0';
		i++;
	}
	new->prev = prms->lcmds;
	new->flag = '2';
	return (new);
}

void	ft_add_char_to_cmd(t_param *prms, char chr)
{
	int		i;
	int		y;

	i = 0;
	if (!prms->lcmds)
	{
		prms->lcmds = ft_malloc_lcmd(prms);
		prms->tmp_argc = 0;
		prms->tmp_argc_fl = 0;
	}
	if (prms->lcmds->cmd[0] == '\0' && ft_isspace(chr)
		&& prms->sq == 0 && prms->dq == 0)
		i = i + 1 - 1;
	else
	{
		prms->lcmds->cmd[ft_strlen(prms->lcmds->cmd)] = chr;
		if ((prms->tmp_argc == 1) && prms->lcmds->str[0][0] == '\0')
			prms->tmp_argc = 0;
		y = prms->tmp_argc;
		if (!(prms->tmp_argc_fl == 1 && ft_isspace(chr)))
			prms->lcmds->str[y][ft_strlen(prms->lcmds->str[y])] = chr;
		prms->tmp_argc_fl = 0;
	}
}

void	ft_lcmd_flag(t_param *prms, char chr1, char chr2)
{
	if (chr1 != '<' && chr1 != '>' && chr1 != '|')
		prms->lcmds->flag = '2';
	else
		prms->lcmds->flag = chr1;
	if (chr1 == '>' && chr2 == '>')
		prms->lcmds->flag = 'd';
}

void	ft_add_new_to_list(t_param *prms, char chr1, char chr2)
{
	t_cmds		*new;

	prms->tmp_argc = 0;
	prms->tmp_argc_fl = 0;
	if (prms->lcmds)
	{
		new = ft_malloc_lcmd(prms);
		ft_lcmd_flag(prms, chr1, chr2);
		prms->lcmds->next = new;
		prms->lcmds = new;
	}
	else
	{
		prms->lcmds = ft_malloc_lcmd(prms);
		ft_lcmd_flag(prms, chr1, chr2);
		new = ft_malloc_lcmd(prms);
		prms->lcmds->next = new;
		prms->lcmds = new;
	}
}
