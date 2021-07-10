/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jandre <jandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 16:36:23 by jandre            #+#    #+#             */
/*   Updated: 2021/07/10 15:59:59 by jandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

static long	ft_negative(char c)
{
	if (c == '-')
		return (-1);
	else
		return (1);
	return (1);
}

int	ft_atol(const char *str)
{
	size_t				i;
	long				neg;
	unsigned long long	retour;

	i = 0;
	neg = 1;
	while (str[i] == ' ' || str[i] == '\n' || str[i] == '\v'
		|| str[i] == '\t' || str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		neg = ft_negative(str[i]);
		i++;
	}
	retour = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		retour = retour * 10 + (str[i] - '0');
		i++;
	}
	return ((long)retour * neg);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (-1);
}

int	ft_isnbr(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isdigit(str[i]) < 0)
			return (-1);
		i++;
	}
	return (1);
}
