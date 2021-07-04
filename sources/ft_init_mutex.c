/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_mutex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jandre <jandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/04 13:57:48 by jandre            #+#    #+#             */
/*   Updated: 2021/07/04 16:51:28 by jandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	wrong_arg(void)
{
	printf("Error : use the program like :\n./philo \"number of \
philosopher\" \"time to die in ms\" \"time to eat in ms\" \"time \
to sleep in ms\" \"optionnal : max number of eating\"\nAll numbers \
must be positive integers\n");
	return (-1);
}

static int	mutex_init(t_philo *ph)
{
	int		i;

	i = 0;
	ph->forks = malloc(sizeof(t_mutex) * ph->fork_nbr);
	ph->display_m = malloc(sizeof(t_mutex));
	pthread_mutex_init(&ph->display_m->mutex, NULL);
	if (!ph->forks)
		return (-1);
	while (i < ph->fork_nbr)
	{
		pthread_mutex_init(&ph->forks[i].mutex, NULL);
		i++;
	}
	return (1);
}

int	init(t_philo *ph, char **argv, int argc)
{
	int	res;

	res = init_mem_val(ph, argv, argc);
	if (res < 0)
	{
		if (res == -1)
			return (wrong_arg());
		return (res);
	}
	res = mutex_init(ph);
	if (res < 0)
		return (res);
	return (1);
}
