/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 20:43:22 by student           #+#    #+#             */
/*   Updated: 2021/05/06 20:43:27 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_putexitnbr(t_param *prms, int n)
{
	if (n < 0)
	{
		ft_add_char_to_cmd(prms, '-');
		n = -n;
	}
	if (n > 9)
	{
		ft_putexitnbr(prms, n / 10);
		ft_putexitnbr(prms, n % 10);
	}
	else
		ft_add_char_to_cmd(prms, n + 48);
}

int	ft_find_env_param(t_param *prms, int i)
{
	t_env		*env;

	env = prms->env;
	ft_erase_str(prms->prm_name);
	i++;
	if (prms->str[i] == '?')
	{
		ft_putexitnbr(prms, prms->exit_status);
		return (++i);
	}
	return (ft_var_name(prms, i, 0));
}

void	ft_add_char(t_param *prms, int i)
{
	if (i > 0)
	{
		if (ft_isspace(prms->str[i]) && ft_isspace(prms->str[i - 1]) \
			&& prms->sq == 0 && prms->dq == 0)
			i = i + 1 - 1;
		else
		{
			if (ft_isspace(prms->str[i]) && prms->sq == 0 && prms->dq == 0)
			{
				prms->tmp_argc++;
				prms->tmp_argc_fl = 1;
			}
			ft_add_char_to_cmd(prms, prms->str[i]);
		}
	}
	else
		ft_add_char_to_cmd(prms, prms->str[i]);
}

int	ft_parce_quotes(t_param *prms, int i)
{
	if (prms->str[i] == '\'' && prms->sq == 0 && prms->dq == 0)
	{
		prms->sq = 1;
		return (1);
	}
	else if (prms->str[i] == '\"' && prms->sq == 0 && prms->dq == 0)
	{
		prms->dq = 1;
		return (1);
	}
	else if (prms->str[i] == '\'' && prms->sq == 1 && prms->dq == 0)
	{
		prms->sq = 0;
		return (1);
	}
	else if (prms->str[i] == '\"' && prms->sq == 0 && prms->dq == 1)
	{
		prms->dq = 0;
		return (1);
	}
	return (0);
}

void	ft_parse_str(t_param *prms, int i)
{
	while (prms->str[i])
	{
		if (prms->str[i] == '\\' && prms->sq == 0)
		{
			ft_add_char_to_cmd(prms, prms->str[++i]);
			i++;
			continue ;
		}
		if (ft_parce_quotes(prms, i) == 1)
		{
			i++;
			continue ;
		}
		if (ft_parse_str2(prms, &i) == 1)
			prms->tmp_argc += 0;
		else if (prms->str[i] == '$' && prms->sq == 0)
		{
			i = ft_find_env_param(prms, i);
			continue ;
		}
		else
			ft_add_char(prms, i);
		i++;
	}
}
