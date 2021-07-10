/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_routine.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jandre <jandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 15:27:39 by jandre            #+#    #+#             */
/*   Updated: 2021/07/10 15:36:23 by jandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	isolated(t_philo ph, int i, void *arg)
{
	if (ph.philo_nbr == 1)
	{
		ft_putnbr(get_time() - *ph.initial_time);
		write(1, " - ", 3);
		ft_putnbr(i);
		write(1, " has taken a fork\n", 18);
		usleep(ph.time_to_die * 1000);
		free(arg);
		return (-1);
	}
	return (1);
}

static int	routine_loop(t_philo ph, int i, int *ate)
{
	if (thinking(ph, i, *ate) < 0)
		return (-1);
	if (eating(ph, i, ate) < 0)
		return (-1);
	if (*ate == ph.max_eating)
		*ph.how_many_ate += 1;
	if (sleeping(ph, i) < 0)
		return (-1);
	return (1);
}

void	*routine(void *arg)
{
	t_philo	ph;
	int		i;
	int		ate;

	ph = *(t_philo *)arg;
	i = ph.index;
	ate = 0;
	ph.last_meal_time[i - 1] = get_time();
	while (*ph.start == 0)
		ph.last_meal_time[i - 1] = get_time();
	if (isolated(ph, i, arg) < 0)
		return (NULL);
	if (i % 2 == 0)
		usleep(200);
	pthread_mutex_unlock(&ph.checker[i - 1].mutex);
	while (*ph.is_dead == 0)
	{
		if (routine_loop(ph, i, &ate) < 0)
			break ;
	}
	free(arg);
	return (NULL);
}
