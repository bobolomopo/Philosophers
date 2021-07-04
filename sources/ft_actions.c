/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_actions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jandre <jandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/04 15:41:33 by jandre            #+#    #+#             */
/*   Updated: 2021/07/04 17:00:45 by jandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	thinking(t_philo ph, int i, int ate)
{
	if (ate != 0)
		display_message(2, ph, i);
	pthread_mutex_lock(&ph.forks[i - 1].mutex);
	pthread_mutex_lock(&ph.forks[i % ph.fork_nbr].mutex);
	display_message(3, ph, i);
	if (*ph.is_dead != 0)
	{
		pthread_mutex_unlock(&ph.forks[i - 1].mutex);
		pthread_mutex_unlock(&ph.forks[i % ph.fork_nbr].mutex);
		return (-1);
	}
	return (1);
}

int	eating(t_philo ph, int i, int *ate)
{
	int	time;

	time = get_time();
	display_message(0, ph, i);
	ph.last_meal_time[i - 1] = get_time();
	*ate += 1;
	while (get_time() - time < ph.time_to_eat
		&& *ph.is_dead == 0)
		usleep(500);
	pthread_mutex_unlock(&ph.forks[i - 1].mutex);
	pthread_mutex_unlock(&ph.forks[i % ph.fork_nbr].mutex);
	if (*ph.is_dead != 0)
		return (-1);
	return (1);
}

int	sleeping(t_philo ph, int i)
{
	int	time;

	time = get_time();
	display_message(1, ph, i);
	while (get_time() - time < ph.time_to_sleep
		&& *ph.is_dead == 0)
		usleep(500);
	if (*ph.is_dead != 0)
		return (-1);
	return (1);
}
