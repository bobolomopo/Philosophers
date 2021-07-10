/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_thread.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jandre <jandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/04 14:36:55 by jandre            #+#    #+#             */
/*   Updated: 2021/07/10 15:42:50 by jandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	copy_struct(t_philo original, t_philo *new)
{
	int	i;

	i = 0;
	new->philo_nbr = original.philo_nbr;
	new->fork_nbr = original.fork_nbr;
	new->time_to_die = original.time_to_die;
	new->time_to_eat = original.time_to_eat;
	new->time_to_sleep = original.time_to_sleep;
	new->max_eating = original.max_eating;
	new->forks = original.forks;
	new->checker = original.checker;
	new->how_many_ate = original.how_many_ate;
	new->is_dead = original.is_dead;
	new->initial_time = original.initial_time;
	new->display_m = original.display_m;
	new->display_m->mutex = original.display_m->mutex;
	new->start = original.start;
	new->last_meal_time = original.last_meal_time;
	while (i < original.fork_nbr)
	{
		new->forks[i].mutex = original.forks[i].mutex;
		new->checker[i].mutex = original.checker[i].mutex;
		i++;
	}
	new->is_limit = original.is_limit;
}

int	create_thread(t_philo ph)
{
	int		i;
	t_philo	*each_ph;

	i = 0;
	while (i < (int)ph.philo_nbr)
	{
		each_ph = malloc(sizeof(t_philo));
		if (!each_ph)
			return (-1);
		copy_struct(ph, each_ph);
		each_ph->index = i + 1;
		pthread_mutex_lock(&ph.checker[i].mutex);
		if (pthread_create(&ph.check_die[i], NULL, &check_die, each_ph) != 0)
			return (-2);
		if (pthread_create(&ph.thread[i], NULL, &routine, each_ph) != 0)
			return (-3);
		i++;
	}
	return (1);
}
