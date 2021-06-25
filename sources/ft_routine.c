/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_routine.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jandre <jandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 15:27:39 by jandre            #+#    #+#             */
/*   Updated: 2021/06/25 12:46:03 by jandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	locks(t_philo ph, int i, int status)
{
	if (status == 0)
	{
		if (i % 2 == 0)
			pthread_mutex_lock(&ph.forks[i - 1].fork);
		else
			pthread_mutex_lock(&ph.forks[i % ph.fork_nbr].fork);
		printf("[%d] %d has taken a fork\n", get_time(), i);
		if (i % 2 == 0)
			pthread_mutex_lock(&ph.forks[i % ph.fork_nbr].fork);
		else
			pthread_mutex_lock(&ph.forks[i - 1].fork);
		printf("[%d] %d has taken a fork\n", get_time(), i);
		return ;
	}
	if (status == 1)
	{
		pthread_mutex_unlock(&ph.forks[i - 1].fork);
		pthread_mutex_unlock(&ph.forks[i % ph.fork_nbr].fork);
	}
	return ;
}

static int	routine_loop(t_philo *ph, int i, int *ate)
{
	int	last_meal;
	
	last_meal = get_time();
	if (thinking(*ph, i, last_meal) < 0)
		return (-1);
	if (eating(*ph, i, last_meal) < 0)
		return (-1);
	locks(*ph, i, 1);
	*ate += 1;
	if (*ate + 1 == ph->max_eating)
		*ph->how_many_ate += 1;
	if (*ph->how_many_ate == ph->philo_nbr && ph->is_limit == 1)
		return (-2);
	if (sleeping(*ph, i, last_meal) < 0)
		return (-1);
	printf("[%d] %d is thinking\n", get_time(), i);
	return (1);
}

void	*routine(void *arg)
{
	t_philo	ph;
	int		i;
	int		*ate;
	int		*res;

	ph = *(t_philo *)arg;
	i = ph.index;
	res = malloc(sizeof(int));
	*res = 0;
	ate = malloc(sizeof(int));
	if (!ate)
		return ((void *)res);
	*ate = 0;
	while (1)
	{
		*res = routine_loop(&ph, i, ate);
		if (*res < 0)
		{
			if (*res == -1)
				printf("[%d] %d died\n", get_time(), i);
			break ;
		}
	}
	free(arg);
	free(ate);
	return ((void *)res);
}
