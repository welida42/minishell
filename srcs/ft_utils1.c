/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 16:17:17 by student           #+#    #+#             */
/*   Updated: 2021/05/06 16:17:54 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_putchar(int c)
{
	write(1, &c, 1);
	return (0);
}

int	ft_strlen(const char *str)
{
	int	length;

	if (!str)
		return (0);
	length = 0;
	while (str[length] != '\0')
		length++;
	return (length);
}

int	ft_isspace(int c)
{
	if (c == ' ' || c == '\n' || c == '\t' || c == '\r' || c == '\v' || c == '\f')
		return (1);
	return (0);
}

void	ft_print_prompt(t_param *prms)
{
	int		length;

	length = ft_strlen(CMD_PROMPT);
	write(2, CMD_PROMPT, length);
	prms->t_pos = length;
	prms->t_start = length;
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if ((!s1) && (!s2))
		return (0);
	if ((!s1) && (s2))
		return (-s2[0]);
	if ((s1) && (!s2))
		return (s1[0]);
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}
