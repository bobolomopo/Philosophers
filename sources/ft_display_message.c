/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display_message.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jandre <jandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 13:34:29 by jandre            #+#    #+#             */
/*   Updated: 2021/07/04 16:52:19 by jandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	ft_putchar(char c)
{
	write (1, &c, 1);
}

void	ft_putnbr(int nb)
{
	if (nb < 0)
	{
		nb = -nb;
	}
	if (nb >= 10)
	{
		ft_putnbr(nb / 10);
		ft_putnbr(nb % 10);
	}
	else
		ft_putchar(nb + '0');
}

void	display_message(int status, t_philo ph, int i)
{
	pthread_mutex_lock(&ph.display_m->mutex);
	if (*ph.is_dead == 0)
	{
		ft_putnbr(get_time() - *ph.initial_time);
		write(1, " - ", 3);
		ft_putnbr(i);
		if (status == 0)
			write(1, " is eating\n", 11);
		if (status == 1)
			write(1, " is sleeping\n", 13);
		if (status == 2)
			write(1, " is thinking\n", 13);
		if (status == 3)
		{
			write(1, " has taken a fork\n", 18);
			ft_putnbr(get_time() - *ph.initial_time);
			write(1, " - ", 3);
			ft_putnbr(i);
			write(1, " has taken a fork\n", 18);
		}
		if (status == 4)
			write(1, " died\n", 6);
	}
	pthread_mutex_unlock(&ph.display_m->mutex);
	return ;
}
