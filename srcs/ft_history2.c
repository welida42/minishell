/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_history2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtawney <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/19 17:36:49 by dtawney           #+#    #+#             */
/*   Updated: 2021/06/19 17:36:56 by dtawney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_read_bash_hist2(t_param *prms, char *tmp_hist, int i, int *y)
{
	tmp_hist[*y] = '\0';
	if (tmp_hist[0])
		ft_add_last_hist(prms, tmp_hist);
	*y = 0;
	return (++i);
}

int	ft_read_bash_hist3(int res, int fd, char *hist, int *i)
{
	res = read(fd, hist, 100);
	if (res > 0)
		*i = 0;
	return (res);
}

int	ft_read_bash_hist4(char *hist, int fd)
{
	ft_erase_str(hist);
	return (read(fd, hist, 100));
}
