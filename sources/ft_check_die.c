/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_die.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jandre <jandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/04 13:34:19 by jandre            #+#    #+#             */
/*   Updated: 2021/07/10 15:36:16 by jandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*check_die(void *arg)
{
	t_philo	ph;
	int		i;

	ph = *(t_philo *)arg;
	i = ph.index;
	pthread_mutex_lock(&ph.checker[i - 1].mutex);
	while (get_time() - ph.last_meal_time[i - 1] <= ph.time_to_die
		&& *ph.is_dead == 0)
	{
		if (ph.is_limit != 0 && *ph.how_many_ate >= ph.philo_nbr)
			break ;
		usleep(500);
	}
	if (get_time() - ph.last_meal_time[i - 1] > ph.time_to_die)
	{
		display_message(4, ph, i);
		*ph.is_dead += 1;
	}
	if (*ph.how_many_ate == ph.philo_nbr)
		*ph.is_dead += 1;
	pthread_mutex_unlock(&ph.checker[i].mutex);
	return (NULL);
}
