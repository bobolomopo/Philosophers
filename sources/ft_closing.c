/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_closing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jandre <jandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/04 14:27:16 by jandre            #+#    #+#             */
/*   Updated: 2021/07/04 16:50:10 by jandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	closing_loop(t_philo ph)
{
	int	i;

	i = 0;
	while (i < ph.philo_nbr)
	{
		if (pthread_join(ph.check_die[i], NULL) != 0)
			return (-1);
		if (pthread_join(ph.thread[i], NULL) != 0)
			return (-1);
		i++;
	}
	return (1);
}

static void	mutex_destroy(t_philo *ph)
{
	int		i;

	i = 0;
	pthread_mutex_destroy(&ph->display_m->mutex);
	while (i < ph->fork_nbr)
	{
		pthread_mutex_destroy(&ph->forks[i].mutex);
		i++;
	}
	free(ph->display_m);
	free(ph->forks);
}

static void	free_all(t_philo ph)
{
	free(ph.how_many_ate);
	free(ph.is_dead);
	free(ph.start);
	free(ph.start_check);
	free(ph.last_meal_time);
	free(ph.check_die);
	free(ph.thread);
	free(ph.initial_time);
	mutex_destroy(&ph);
	return ;
}

int	closing(t_philo ph)
{
	if (closing_loop(ph) < 0)
		return (-1);
	free_all(ph);
	return (1);
}
