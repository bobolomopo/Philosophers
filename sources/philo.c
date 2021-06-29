/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jandre <ajuln@hotmail.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/19 14:56:25 by jandre            #+#    #+#             */
/*   Updated: 2021/06/29 16:12:44 by jandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	wrong_arg(void)
{
	printf("Error : use the program like :\n./philo \"number of \
philosopher, minimum two, need two fork to eat\" \"time to die in ms\" \
\"time to eat in ms\" \"time to sleep in ms\" \"optionnal : max number of \
eating\"\nAll numbers must be positive integers\n");
	return (-1);
}

void	copy_struct(t_philo original, t_philo *new)
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
	new->how_many_ate = original.how_many_ate;
	new->is_dead = original.is_dead;
	new->initial_time = original.initial_time;
	while (i < original.fork_nbr)
	{
		new->forks[i].fork = original.forks[i].fork;
		i++;
	}
	new->is_limit = original.is_limit;
}

static void	free_all(t_philo ph)
{
	free(ph.how_many_ate);
	free(ph.is_dead);
	free(ph.thread);
	mutex_destroy(&ph);
	return ;
}

int	main(int argc, char **argv)
{
	t_philo	ph;
	t_philo	*each_ph;
	int		i;

	i = 0;
	if (init(&ph, argv, argc) < 0)
		return (-1);
	while (i < (int)ph.philo_nbr)
	{
		each_ph = malloc(sizeof(t_philo));
		if (!each_ph)
			return (-1);
		copy_struct(ph, each_ph);
		each_ph->index = i + 1;
		if (pthread_create(&ph.thread[i], NULL, &routine, each_ph) != 0)
			return (thread_error(0));
		i++;
	}
	i = 0;
	if (closing_loop(ph) < 0)
		return (-1);
	free_all(ph);
	return (0);
}
