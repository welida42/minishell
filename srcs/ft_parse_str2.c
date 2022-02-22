/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_str2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtawney <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/20 14:18:21 by dtawney           #+#    #+#             */
/*   Updated: 2021/06/20 14:18:24 by dtawney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_var_name(t_param *prms, int i, int n)
{
	if ((prms->str[i] >= 'A' && prms->str[i] <= 'Z') || \
		(prms->str[i] >= 'a' && prms->str[i] <= 'z'))
		prms->prm_name[n++] = prms->str[i++];
	while (n > 0 && ((prms->str[i] >= '0' && prms->str[i] <= '9') || \
		(prms->str[i] >= 'A' && prms->str[i] <= 'Z') || \
		(prms->str[i] >= 'a' && prms->str[i] <= 'z')))
	{
		prms->prm_name[n++] = prms->str[i++];
	}
	prms->prm_name[n] = '\0';
	prms->prm_res = find_var_env(prms->envp, prms->prm_name);
	n = 0;
	if (prms->prm_res)
	{
		while (prms->prm_res[n] && prms->prm_res[n] != '=')
			n++;
		if (prms->prm_res[n] == '=')
			n++;
		while (prms->prm_res[n])
			ft_add_char_to_cmd(prms, prms->prm_res[n++]);
	}
	return (i);
}

int	ft_parse_str2(t_param *prms, int *i)
{
	if ((prms->str[*i] == '|' || prms->str[*i] == '<' || prms->str[*i] == '>') \
		&& (prms->sq == 0 && prms->dq == 0))
	{
		ft_add_new_to_list(prms, prms->str[*i], prms->str[*i + 1]);
		if (prms->str[*i] == '>' && prms->str[*i + 1] == '>')
			*i = *i + 1;
		return (1);
	}
	else if (prms->str[*i] == ';' && prms->sq == 0 && prms->dq == 0)
	{
		ft_add_new_to_list(prms, prms->str[*i], prms->str[*i + 1]);
		return (1);
	}
	return (0);
}
