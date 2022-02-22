/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtawney <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 12:18:00 by dtawney           #+#    #+#             */
/*   Updated: 2021/06/14 12:18:13 by dtawney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	sig_handler(int sig)
{
	int		pid;
	int		status;

	pid = waitpid(0, &status, WNOHANG);
	if (pid < 0)
	{
		if (sig == SIGQUIT)
		{
			write(2, "1", 0);
		}
		if (sig == SIGINT)
		{
			write(2, "\n", 1);
			write(1, CMD_PROMPT, ft_strlen(CMD_PROMPT));
			g_sig = 1;
		}
	}
	else
	{
		if (sig == SIGINT)
			write(2, "\n", 1);
		if (sig == SIGQUIT)
			write(2, "Quit: 3\n", 8);
	}
}

void	sig_handler3(int sig)
{
	if (sig == SIGINT)
	{
		write(2, "^C\n", 3);
	}
}

void	sig_choise(t_param *prms, int num)
{
	if (num == 1)
	{
		signal(SIGINT, sig_handler);
		signal(SIGQUIT, sig_handler);
		signal(SIGSTOP, sig_handler);
	}
	else
	{
		signal(SIGINT, sig_handler3);
		signal(SIGQUIT, sig_handler3);
		signal(SIGSTOP, sig_handler3);
	}
	prms->tmp_argc += 0;
}
