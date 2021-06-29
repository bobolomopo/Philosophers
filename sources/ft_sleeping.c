/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sleeping.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jandre <ajuln@hotmail.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 15:43:41 by jandre            #+#    #+#             */
/*   Updated: 2021/06/29 16:32:07 by jandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	eating(t_philo ph, int i, int *last_meal)
{
	if (get_time() - *last_meal > ph.time_to_die)
		return (-1);
	if (*ph.is_dead == 0)
	{
		printf("[%d] %d is eating\n", (get_time() - ph.initial_time), i);
		usleep(ph.time_to_eat * 1000);
		*last_meal = get_time();
	}
	else
		return (-2);
	return (1);
}

int	sleeping(t_philo ph, int i, int last_meal)
{
	int	time;

	time = get_time();
	if (*ph.is_dead == 0)
	{
		printf("[%d] %d is sleeping\n", (get_time() - ph.initial_time), i);
		while (get_time() - time < ph.time_to_sleep
			&& get_time() - last_meal < ph.time_to_die)
			usleep(10000);
		if (get_time() - last_meal < ph.time_to_die)
		{
			if (*ph.is_dead == 0)
				printf("[%d] %d is thinking\n", get_time() - ph.initial_time, i);
			return (1);
		}
		else
			return (-1);
	}
	else
		return (-2);
}

int	thinking(t_philo ph, int i, int last_meal)
{
	int fork_one;
	int	fork_two;

	fork_one = 1;
	fork_two = 1;
	while (get_time() - last_meal < ph.time_to_die)
	{
		fork_one = pthread_mutex_trylock(&ph.forks[i - 1].fork);
		fork_two = pthread_mutex_trylock(&ph.forks[i % ph.fork_nbr].fork);
		if (fork_one == 0 && fork_two == 0)
			break ;
		if (fork_one == 0)
			pthread_mutex_unlock(&ph.forks[i - 1].fork);
		if (fork_two == 0)
			pthread_mutex_unlock(&ph.forks[i % ph.fork_nbr].fork);
	}
	if (get_time() - last_meal > ph.time_to_die)
		return (-1);
	if (*ph.is_dead == 0)
	{
		printf("[%d] %d has taken a fork\n", (get_time() - ph.initial_time), i);
		printf("[%d] %d has taken a fork\n", (get_time() - ph.initial_time), i);
		return (1);
	}
	else
		return (-2);
}
