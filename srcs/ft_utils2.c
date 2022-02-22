/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 18:01:09 by student           #+#    #+#             */
/*   Updated: 2021/05/06 18:01:14 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_our_ft(char *cmd)
{
	if (!ft_strcmp(cmd, "env") || !ft_strcmp(cmd, "export") || \
		!ft_strcmp(cmd, "echo") || !ft_strcmp(cmd, "unset") || \
		!ft_strcmp(cmd, "cd") || !ft_strcmp(cmd, "pwd") || \
		!ft_strcmp(cmd, "exit"))
		return (1);
	return (0);
}

void	ft_erase_str(char *str)
{
	int	i;

	i = 0;
	while (i < 2000)
		str[i++] = '\0';
}

void	ft_copy_str(t_param *prms, char *str)
{
	int		i;

	i = 0;
	if (prms->t_pos >= prms->t_start)
		while (str[i] && i < (BUFFER_SIZE - prms->t_start))
			prms->str[prms->t_pos++ - prms->t_start] = str[i++];
}

char	*ft_strdup(const char *s1)
{
	char	*dest;
	int		length;

	if (!s1)
		return (0);
	length = 0;
	while (s1[length])
		length++;
	dest = (char *)malloc(sizeof(char) * (length + 1));
	if (dest == NULL)
		return (NULL);
	dest[length + 1] = '\0';
	while (length >= 0)
	{
		dest[length] = s1[length];
		--length;
	}
	return (dest);
}

int	ft_strncmp(const char *s1, const char *s2, int n)
{
	int		i;

	i = 0;
	while ((i < n) && (s1[i] != '\0'))
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		++i;
	}
	if ((i == n) || (s2[i] == '\0'))
		return (0);
	else
		return (s1[i] - s2[i]);
}
