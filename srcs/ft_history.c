/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_history.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/09 21:04:34 by student           #+#    #+#             */
/*   Updated: 2021/05/09 21:05:31 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_add_last_hist2(t_hist *cur, t_hist *new, t_hist *prev, char *t_h)
{
	cur->next = new;
	cur = new;
	cur->next = NULL;
	cur->previous = prev;
	cur->value = ft_strdup(t_h);
}

int	ft_add_last_hist(t_param *prms, char *tmp_hist)
{
	t_hist	*previous;
	t_hist	*current;
	t_hist	*new;

	if (!prms->hist)
	{
		prms->hist = malloc(sizeof(t_hist));
		if (!prms->hist)
			return (1);
		prms->hist->previous = NULL;
		prms->hist->next = NULL;
		prms->hist->value = ft_strdup(tmp_hist);
	}
	else
	{
		current = prms->hist;
		while (current && current->next)
			current = current->next;
		previous = current;
		new = malloc(sizeof(t_hist));
		if (!new)
			return (1);
		ft_add_last_hist2(current, new, previous, tmp_hist);
	}
	return (0);
}

void	ft_to_last_hist(t_param *prms)
{
	while (prms->hist)
	{
		if (prms->hist->next)
			prms->hist = prms->hist->next;
		else
			break ;
	}
}

void	ft_read_bash_hist(t_param *prms, int i, int y, char *path)
{
	char		tmp_hist[2000];
	char		hist[2000];
	int			fd;
	int			res;

	fd = open(path, O_RDONLY);
	if (fd > 2)
	{
		res = ft_read_bash_hist4(hist, fd);
		while (hist[i] && i < 100 && res > 0)
		{
			while (i < res && hist[i] && hist[i] != '\n')
				tmp_hist[y++] = hist[i++];
			if (i != res)
				i = ft_read_bash_hist2(prms, tmp_hist, i, &y);
			if (i == res && res > 0 && res == 100)
			{
				res = ft_read_bash_hist3(res, fd, hist, &i);
				if (res <= 0)
					break ;
			}
			if (i == res && res > 0 && res != 100)
				break ;
		}
	}
}

void	ft_copy_history(t_param *prms)
{
	int			i;
	int			y;
	char		path[200];
	char		*path2;

	path2 = find_var_env(prms->envp, "HOME");
	if (!(path2) || !ft_strcmp(path2, "HOME="))
		ft_add_last_hist(prms, "no history((");
	else
	{
		path2 += ft_strlen("HOME") + 1;
		i = -1;
		while (path2[++i])
			path[i] = path2[i];
		path[i] = '\0';
		y = 0;
		while (HIST_FILE[y])
			path[i++] = HIST_FILE[y++];
		path[i] = '\0';
		if (path[0])
			ft_read_bash_hist(prms, 0, 0, path);
		ft_to_last_hist(prms);
	}
}
