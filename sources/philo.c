/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jandre <jandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/19 14:56:25 by jandre            #+#    #+#             */
/*   Updated: 2021/07/10 15:40:00 by jandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	main(int argc, char **argv)
{
	t_philo	ph;
	int		i;

	i = 0;
	if (init(&ph, argv, argc) < 0)
		return (-1);
	if (create_thread(ph) < 0)
		return (-2);
	*ph.initial_time = get_time();
	*ph.start = 1;
	usleep(1000);
	if (closing(ph) < 0)
		return (-3);
	return (0);
}
