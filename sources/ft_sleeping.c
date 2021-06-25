/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sleeping.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jandre <jandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 15:43:41 by jandre            #+#    #+#             */
/*   Updated: 2021/06/25 15:44:17 by jandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	eating(t_philo ph, int i, int last_meal)
{
	long	time;

	time = 0;
	printf("[%d] %d is eating\n", (get_time() - ph.initial_time), i);
	while (time < ph.time_to_eat && get_time() - last_meal < ph.time_to_die)
	{
		usleep(10000);
		time += 10;
	}
	if (get_time() - last_meal < ph.time_to_die)
		return (1);
	else
		return (-1);
}

int	sleeping(t_philo ph, int i, int last_meal)
{
	long	time;

	time = 0;
	printf("[%d] %d is sleeping\n", (get_time() - ph.initial_time), i);
	while (time < ph.time_to_sleep && get_time() - last_meal < ph.time_to_die)
	{
		usleep(10000);
		time += 10;
	}
	if (get_time() - last_meal < ph.time_to_die)
		return (1);
	else
		return (-1);
}

static int	first_fork(t_philo ph, int i, int last_meal)
{
	if (i % 2 == 0)
	{
		while (pthread_mutex_trylock(&ph.forks[i - 1].fork) != 0)
		{
			if (get_time() - last_meal > ph.time_to_die)
				return (-1);
		}
	}
	else
	{
		while (pthread_mutex_trylock(&ph.forks[i % ph.fork_nbr].fork) != 0)
		{
			if (get_time() - last_meal > ph.time_to_die)
				return (-1);
		}
	}
	printf("[%d] %d has taken a fork\n", (get_time() - ph.initial_time), i);
	return (1);
}

static int	second_fork(t_philo ph, int i, int last_meal)
{
	if (i % 2 == 0)
	{
		while (pthread_mutex_trylock(&ph.forks[i % ph.fork_nbr].fork) != 0)
		{
			if (get_time() - last_meal > ph.time_to_die)
				return (-1);
		}
	}
	else
	{
		while (pthread_mutex_trylock(&ph.forks[i - 1].fork) != 0)
		{
			if (get_time() - last_meal > ph.time_to_die)
				return (-1);
		}
	}
	printf("[%d] %d has taken a fork\n", (get_time() - ph.initial_time), i);
	return (1);
}

int	thinking(t_philo ph, int i, int last_meal)
{
	if (first_fork(ph, i, last_meal) < 0)
		return (-1);
	if (second_fork(ph, i, last_meal) < 0)
		return (-1);
	return (1);
}
