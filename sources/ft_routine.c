/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_routine.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jandre <ajuln@hotmail.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 15:27:39 by jandre            #+#    #+#             */
/*   Updated: 2021/06/29 16:36:22 by jandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	routine_loop(t_philo *ph, int i, int *ate, int *last_meal)
{
	int res;

	res = thinking(*ph, i, *last_meal);
	if (res < 0)
		return (res);
	res = eating(*ph, i, last_meal);
	*ate += 1;
	if (res < 0)
		return (res);
	pthread_mutex_unlock(&ph->forks[i - 1].fork);
	pthread_mutex_unlock(&ph->forks[i % ph->fork_nbr].fork);
	if (*ate == ph->max_eating)
		*ph->how_many_ate += 1;
	if ((*ph->how_many_ate == ph->philo_nbr && ph->is_limit == 1)
		|| *ph->is_dead > 0)
		return (-2);
	res = sleeping(*ph, i, *last_meal);
	if (res < 0)
		return (res);
	return (1);
}

static int	cond_loop(int *res, t_philo *ph, int i)
{
	if (*res < 0)
	{
		if (*res == -1)
		{
			if (*ph->is_dead == 0)
				printf("[%d] %d died\n", get_time() - ph->initial_time, i);
			*ph->is_dead += 1;
		}
		return (-1);
	}
	return (1);
}

static void	free_all(int *ate, int *last_meal, void *arg)
{
	free(ate);
	free(last_meal);
	free(arg);
	return ;
}

static void	init_values_routine(int *res, int *last_meal, int *ate)
{
	*res = 0;
	*last_meal = get_time();
	*ate = 1;
	return ;
}

void	*routine(void *arg)
{
	t_philo	ph;
	int		i;
	int		*ate;
	int		*res;
	int		*last_meal;

	ph = *(t_philo *)arg;
	i = ph.index;
	res = malloc(sizeof(int));
	ate = malloc(sizeof(int));
	last_meal = malloc(sizeof(int));
	if (!ate || !res || !last_meal)
		return ((void *)res);
	init_values_routine(res, last_meal, ate);
	printf("[%d] %d initial time\n", (get_time() - ph.initial_time), i);
	while (1)
	{
		if (*ph.is_dead > 0)
			break ;
		*res = routine_loop(&ph, i, ate, last_meal);
		if (cond_loop(res, &ph, i) < 0)
			break ;
	}
	free_all(ate, last_meal, arg);
	return ((void *)res);
}
