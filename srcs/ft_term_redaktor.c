/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_term_redaktor.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 16:25:44 by student           #+#    #+#             */
/*   Updated: 2021/05/06 16:25:53 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_check_keys(t_param *prms)
{
	char	*cline;

	cline = prms->cline;
	if (!ft_strcmp(cline, "\e[H"))
	{
		tputs(restore_cursor, 1, ft_putchar);
		prms->t_pos = prms->t_start;
	}
	else if (!ft_strcmp(cline, "\e[F"))
		ft_key_end(prms);
	else if (!ft_strcmp(cline, "\t"))
		prms->t_pos += 0;
	else if (!ft_strcmp(cline, "\eOP") || !ft_strcmp(cline, "\eOQ")
		|| !ft_strcmp(cline, "\eOR") || !ft_strcmp(cline, "\eOS")
		|| !ft_strcmp(cline, "\e[15~") || !ft_strcmp(cline, "\e[17~")
		|| !ft_strcmp(cline, "\e[18~") || !ft_strcmp(cline, "\e[19~")
		|| !ft_strcmp(cline, "\e[20~") || !ft_strcmp(cline, "\e[21~"))
		prms->t_pos += 0;
	else if (cline[0] > 31 && cline[0] < 127)
		ft_key_printable(prms);
}

void	ft_exit_d(t_param *prms)
{
	write(2, "exit\n", 5);
	exit(prms->exit_status);
}

void	ft_signal_happened(t_param *prms)
{
	ft_erase_str(prms->str);
	prms->t_pos = prms->t_start;
	tputs(save_cursor, 1, ft_putchar);
	g_sig = 0;
}

void	ft_check_keys2(t_param *prms)
{
	if (!ft_strcmp(prms->cline, "\x7f"))
		ft_key_backspace(prms);
	else if (!ft_strcmp(prms->cline, "\n"))
		ft_key_enter(prms);
	else if (!ft_strcmp(prms->cline, "\e[3~"))
		ft_key_delete(prms);
	else if (!ft_strcmp(prms->cline, "\4") && prms->str[0] == '\0')
		ft_exit_d(prms);
	else
		ft_check_keys(prms);
}

void	ft_term_redaktor(t_param *prms)
{
	char	*cline;

	while (1)
	{
		prms->res = read(0, prms->cline, 100);
		if (g_sig == 1)
			ft_signal_happened(prms);
		prms->cline[prms->res] = 0;
		cline = prms->cline;
		if (!ft_strcmp(cline, "\e[A") || !ft_strcmp(cline, "\e[5~"))
			ft_key_up(prms);
		else if (!ft_strcmp(cline, "\e[B") || !ft_strcmp(cline, "\e[6~"))
			ft_key_down(prms);
		else if (!ft_strcmp(prms->cline, "\e[D"))
			ft_key_left(prms);
		else if (!ft_strcmp(prms->cline, "\e[C"))
			ft_key_right(prms);
		else
			ft_check_keys2(prms);
	}
}
