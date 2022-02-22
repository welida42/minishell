/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_keys1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 16:29:33 by student           #+#    #+#             */
/*   Updated: 2021/05/06 16:29:36 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_key_up(t_param *prms)
{
	tputs(restore_cursor, 1, ft_putchar);
	tputs(clr_eol, 1, ft_putchar);
	ft_erase_str(prms->str);
	prms->t_pos = prms->t_start;
	if (prms->hist_fl == 2 && prms->hist->previous && prms->hist->next)
		prms->hist = prms->hist->previous;
	if (prms->hist->previous)
	{
		write(1, prms->hist->value, ft_strlen(prms->hist->value));
		ft_copy_str(prms, prms->hist->value);
		prms->t_pos = prms->t_start + ft_strlen(prms->hist->value);
		prms->hist = prms->hist->previous;
	}
	prms->hist_fl = 1;
}

void	ft_key_down(t_param *prms)
{
	tputs(restore_cursor, 1, ft_putchar);
	tputs(clr_eol, 1, ft_putchar);
	ft_erase_str(prms->str);
	prms->t_pos = prms->t_start;
	if (prms->hist_fl == 1 && prms->hist->next && prms->hist->previous)
		prms->hist = prms->hist->next;
	if (prms->hist->next)
	{
		prms->hist = prms->hist->next;
		write(1, prms->hist->value, ft_strlen(prms->hist->value));
		ft_copy_str(prms, prms->hist->value);
		prms->t_pos = prms->t_start + ft_strlen(prms->hist->value);
	}
	prms->hist_fl = 2;
}

void	ft_key_backspace(t_param *prms)
{
	int		i;

	if (prms->t_pos > prms->t_start)
	{
		tputs(cursor_left, 1, ft_putchar);
		prms->t_pos--;
	}
	tputs(delete_character, 1, ft_putchar);
	i = prms->t_pos - prms->t_start;
	if (i >= 0)
	{
		while (prms->str[i])
		{
			prms->str[i] = prms->str[i + 1];
			i++;
		}
	}
}

void	ft_key_delete(t_param *prms)
{
	int		i;

	tputs(delete_character, 1, ft_putchar);
	i = prms->t_pos - prms->t_start;
	if (i >= 0)
	{
		while (prms->str[i])
		{
			prms->str[i] = prms->str[i + 1];
			i++;
		}
	}
}

//only for test print_lcmd_list
/*void print_lcmd_list(t_param *prms)
{
	t_cmds		*tmp;
	int			i;

	if (prms->lcmds)
	{
		tmp = prms->lcmds;
		printf("current_pos:%p--%p\n", tmp, tmp->prev);
		while (tmp->prev)
		{
			tmp = tmp->prev;
			printf("tmp->prev:cur-%p-prev-%p-next-%p-\n",tmp, tmp->prev, tmp->next);
		}
		while (tmp->next)
		{
			printf("command:%s--%c--%p--%p--\n", tmp->cmd, tmp->flag, tmp, tmp->next);
			i = 0;
			if (tmp->str)
				while(tmp->str[i] && i < 32)
				{
					printf("argv[%d]:\"%s\"\n", i, tmp->str[i]);
					i++;
				}
			tmp = tmp->next;
		}
		printf("last command:%s--%c--%p--%p--\n", tmp->cmd, tmp->flag, tmp, tmp->next);
		i = 0;
			if (tmp->str)
				while(tmp->str[i] && i < 32)
				{
					printf("argv[%d]:\"%s\"\n", i, tmp->str[i]);
					i++;
				}
	}
	else
		printf("list is empty\n");
}*/

void	ft_key_enter(t_param *prms)
{
	write(1, "\n", 1);
	if (ft_strlen(prms->str) > 0)
	{
		ft_add_last_hist(prms, prms->str);
		while (prms->hist->next)
			prms->hist = prms->hist->next;
		prms->dq = 0;
		prms->sq = 0;
		if (prms->str[0] != '\0')
			ft_parse_str(prms, 0);
		if (prms->dq == 1 || prms->sq == 1)
			write(2, "error: unclosed quotes\n", 23);
		else
		{
			ft_pipes(prms);
		}
	}
	term_init2(*prms);
	ft_free_lcmds(prms);
	ft_erase_str(prms->str);
	ft_print_prompt(prms);
	tputs(save_cursor, 1, ft_putchar);
}
