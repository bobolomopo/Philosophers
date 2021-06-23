/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_routine.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jandre <jandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 15:27:39 by jandre            #+#    #+#             */
/*   Updated: 2021/06/23 16:33:18 by jandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	locks(t_philo ph, int i, int status)
{
	if (status == 0)
	{
		pthread_mutex_lock(&ph.forks[i - 1].fork);
		if (i == 0)
			pthread_mutex_lock(&ph.forks[ph.fork_nbr - 1].fork);
		else
			pthread_mutex_lock(&ph.forks[i - 2].fork);
	}
	if (status == 1)
	{
		pthread_mutex_unlock(&ph.forks[i - 1].fork);
		if (i == 0)
			pthread_mutex_unlock(&ph.forks[ph.fork_nbr - 1].fork);
		else
			pthread_mutex_unlock(&ph.forks[i - 2].fork);
	}
	return ;
}

static int	is_dead(int last_meal, t_philo ph, int i, int *res)
{
	if (get_time() - last_meal > ph.time_to_die)
	{
		printf("[timestamp : %d] philosophers %d died\n", get_time(), i);
		*res = -1;
		return (-1);
	}
	return (1);
}

static void	sleep_eat(int activity, int last_meal, t_philo ph, int i)
{
	if (activity == 0)
	{
		printf("[timestamp : %d] philosophers %d eating...\n", last_meal, i);
		usleep(ph.time_to_eat * 1000);
	}
	if (activity == 1)
	{
		printf("[timestamp : %d] philosophers %d sleeping...\n", get_time(), i);
		usleep(ph.time_to_sleep * 1000);
	}
	return ;
}

static int	routine_loop(t_philo *ph, int i, int last_meal, int *res)
{
	locks(*ph, i, 0);
	last_meal = get_time();
	sleep_eat(0, last_meal, *ph, i);
	locks(*ph, i, 1);
	if (is_dead(last_meal, *ph, i, res) < 0)
		return (-1);
	sleep_eat(1, last_meal, *ph, i);
	if (is_dead(last_meal, *ph, i, res) < 0)
		return (-1);
	printf("[timestamp : %d] philosophers %d thinking...\n", get_time(), i);
	if (is_dead(last_meal, *ph, i, res) < 0)
		return (-1);
	if (ph->is_limit > 0)
		ph->max_eating--;
	return (1);
}

void	*routine(void *arg)
{
	int		i;
	t_philo	ph;
	int		last_meal;
	int		*res;

	ph = *(t_philo *)arg;
	i = ph.index;
	res = malloc(sizeof(int));
	*res = 0;
	last_meal = 0;
	while (ph.max_eating > 0)
	{
		if (routine_loop(&ph, i, last_meal, res) < 0)
			break ;
	}
	free(arg);
	return ((void *)res);
}
