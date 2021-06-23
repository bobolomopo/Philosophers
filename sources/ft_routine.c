/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_routine.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jandre <jandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 15:27:39 by jandre            #+#    #+#             */
/*   Updated: 2021/06/23 19:15:39 by jandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	locks(t_philo ph, int i, int status)
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

static int	is_dead(int last_meal, t_philo ph, int i, int *res)
{
	if (get_time() - last_meal > ph.time_to_die)
	{
		printf("[%d] %d died\n", get_time(), i);
		*res = -1;
		return (-1);
	}
	return (1);
}

static void	sleep_eat(int activity, int last_meal, t_philo ph, int i)
{
	if (activity == 0)
	{
		printf("[%d] %d is eating\n", last_meal, i);
		usleep(ph.time_to_eat * 1000);
	}
	if (activity == 1)
	{
		printf("[%d] %d is sleeping\n", get_time(), i);
		usleep(ph.time_to_sleep * 1000);
	}
	return ;
}

static int	routine_loop(t_philo *ph, int i, int *res)
{
	int	last_meal;

	locks(*ph, i, 0);
	last_meal = get_time();
	sleep_eat(0, last_meal, *ph, i);
	locks(*ph, i, 1);
	if (is_dead(last_meal, *ph, i, res) < 0)
		return (-1);
	sleep_eat(1, last_meal, *ph, i);
	if (is_dead(last_meal, *ph, i, res) < 0)
		return (-1);
	printf("[%d] %d is thinking\n", get_time(), i);
	if (ph->is_limit > 0)
		ph->max_eating--;
	return (1);
}

void	*routine(void *arg)
{
	int		i;
	t_philo	ph;
	int		*res;

	ph = *(t_philo *)arg;
	i = ph.index;
	res = malloc(sizeof(int));
	*res = 0;
	while (ph.max_eating > 0)
	{
		if (routine_loop(&ph, i, res) < 0)
			break ;
	}
	free(arg);
	return ((void *)res);
}
