/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_keys2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 17:46:49 by student           #+#    #+#             */
/*   Updated: 2021/05/06 17:46:54 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_key_left(t_param *prms)
{
	if (prms->t_pos > prms->t_start)
	{
		tputs(cursor_left, 1, ft_putchar);
		prms->t_pos--;
	}
}

void	ft_key_right(t_param *prms)
{
	if (prms->str[prms->t_pos - prms->t_start])
	{
		tputs(cursor_right, 1, ft_putchar);
		prms->t_pos++;
	}
}

void	ft_key_end(t_param *prms)
{
	while (prms->str[prms->t_pos - prms->t_start])
	{
		tputs(cursor_right, 1, ft_putchar);
		prms->t_pos++;
	}
}

void	ft_key_printable(t_param *prms)
{
	write(1, prms->cline, prms->res);
	ft_copy_str(prms, prms->cline);
}
