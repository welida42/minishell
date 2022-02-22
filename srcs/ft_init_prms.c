/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_prms.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 12:55:26 by student           #+#    #+#             */
/*   Updated: 2021/05/08 12:55:31 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_init_prms(t_param *prms)
{
	prms->exit_status = 0;
	prms->dq = 0;
	prms->sq = 0;
	prms->t_pos = 0;
	prms->t_start = 0;
	prms->hist = NULL;
	prms->hist_fl = 0;
	prms->lcmds = NULL;
	ft_erase_str(prms->str);
	ft_erase_str(prms->command);
	ft_erase_str(prms->cline);
	g_sig = 0;
}

int	ft_init_env(t_param *prms, char const **envp)
{
	t_env	*env;
	t_env	*new;
	int		i;

	env = malloc(sizeof(t_env));
	if (!env)
		return (1);
	env->value = ft_strdup(envp[0]);
	env->next = NULL;
	prms->env = env;
	i = 1;
	while (envp && envp[0] && envp[i])
	{
		new = malloc(sizeof(t_env));
		if (!new)
			return (1);
		new->value = ft_strdup(envp[i]);
		new->next = NULL;
		env->next = new;
		env = new;
		i++;
	}
	return (0);
}
