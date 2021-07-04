/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jandre <jandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 16:36:23 by jandre            #+#    #+#             */
/*   Updated: 2021/07/04 16:51:37 by jandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

/*int	thread_error(int status)
{
	if (status == 0)
		printf("ERROR : could not create thread\n");
	if (status == 1)
		printf("ERROR : could not join thread\n");
	if (status == 2)
		printf("ERROR : could not malloc structures\n");
	if (status == 3)
		printf("ERROR : could not malloc mutexes\n");
	return (-1);
}

int	closing_loop(t_philo ph)
{
	int	i;
	
	i = 0;
	while (i < ph.philo_nbr)
	{
		if (pthread_join(ph.check_die[i], NULL) != 0)
			return (thread_error(1));
		if (pthread_join(ph.thread[i], NULL) != 0)
			return (thread_error(1));
		i++;
	}
	return (1);
}*/

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
