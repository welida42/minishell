/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtawney <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/12 17:51:02 by dtawney           #+#    #+#             */
/*   Updated: 2021/06/12 17:53:25 by dtawney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	sumlen;
	size_t	i;
	char	*p;

	if (!s1 || !s2)
		return (NULL);
	sumlen = ft_strlen(s1) + ft_strlen(s2);
	p = malloc(sizeof(char) * (sumlen + 1));
	if (p == NULL)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		p[i] = s1[i];
		i++;
	}
	while (i < sumlen)
	{
		p[i] = s2[i - ft_strlen(s1)];
		i++;
	}
	p[sumlen] = '\0';
	return (p);
}

int	ft_atoi(const char *str)
{
	int			znak;
	long long	result;
	long long	prev_res;

	znak = 1;
	result = 0;
	while (((*str >= 9) && (*str <= 13)) || (*str == ' '))
		str++;
	if ((*str == '+') || (*str == '-'))
	{
		if (*str == '-')
			znak = -1;
		str++;
	}
	while ((*str >= '0') && (*str <= '9'))
	{
		prev_res = result;
		result = result * 10 + znak * (*str++ - '0');
		if (znak == 1 && prev_res > result)
			return (-1);
		if (znak == -1 && prev_res < result)
			return (0);
	}
	return (result);
}

//static int	ft_numlength(unsigned int n)
//{
//	unsigned int	i;
//
//	i = 0;
//	while (n >= 10)
//	{
//		n = n / 10;
//		++i;
//	}
//	return (i + 1);
//}
//
//char	*ft_itoa(int n)
//{
//	char			*dest;
//	unsigned int	len;
//	unsigned int	num;
//	unsigned int	i;
//
//	num = (n < 0 ? -n : n);
//	len = ft_numlength(num);
//	i = 0;
//	if (!(dest = (char *)malloc(sizeof(char) * len + 1 + (n < 0 ? 1 : 0))))
//		return (NULL);
//	if (n < 0)
//	{
//		dest[i] = '-';
//		++len;
//	}
//	i = len - 1;
//	while (num >= 10)
//	{
//		dest[i] = num % 10 + '0';
//		num = num / 10;
//		--i;
//	}
//	dest[i] = num % 10 + '0';
//	dest[len] = '\0';
//	return (dest);
//}

static size_t	ft_len_number(long number)
{
	int	i;

	i = 1;
	if (number < 0)
	{
		number *= -1;
		i++;
	}
	while (number > 9)
	{
		number /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char	*str;
	long	number;
	size_t	len;

	number = (long)n;
	len = ft_len_number(number);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (str == NULL)
		return (NULL);
	str[len] = '\0';
	if (number < 0)
	{
		str[0] = '-';
		number *= -1;
	}
	while (number > 9)
	{
		len--;
		str[len] = (number % 10) + '0';
		number /= 10;
	}
	str[len - 1] = number + '0';
	return (str);
}
