/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jandre <jandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 16:36:23 by jandre            #+#    #+#             */
/*   Updated: 2021/06/25 12:38:47 by jandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	thread_error(int status)
{
	if (status == 0)
		printf("ERROR : could not create thread\n");
	if (status == 1)
		printf("ERROR : could not join thread\n");
	if (status == 2)
		printf("ERROR : could not malloc structures\n");
	if (status == 3)
		printf("ERROR : could not malloc mutexes\n");
	return (-1);
}

int	init(t_philo *ph, char **argv, int argc)
{
	if (argc != 5 && argc != 6)
		return (wrong_arg());
	if (init_struc(ph, argv) < 0)
		return (wrong_arg());
	if (malloc_struc(ph) < 0)
		return (-1);
	if (mutex_init(ph) < 0)
		return (-1);
	return (1);
}

int	closing_loop(t_philo ph)
{
	int	i;
	int	*res;

	i = 0;
	while (i < ph.philo_nbr)
	{
		if (pthread_join(ph.thread[i], (void **)&res) != 0)
			return (thread_error(1));
		if (*res == -1)
		{
			free(ph.how_many_ate);
			free(ph.thread);
			mutex_destroy(&ph);
			free(res);
			return (-1);
		}
		free(res);
		i++;
	}
	return (1);
}
