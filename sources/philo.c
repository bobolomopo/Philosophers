/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jandre <jandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/19 14:56:25 by jandre            #+#    #+#             */
/*   Updated: 2021/06/21 14:29:51 by jandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	wrong_arg(void)
{
	write(1, "Error : use the program like :\n./philo \"number of \
philosopher\" \"time to die in ms\" \"time to eat in ms\" \"time to \
sleep in ms\" \"optionnal : max number of eating\"\nAll numbers must \
be positive integers\n", 198);
	return (1);
}

void	*routine()
{
	printf("yes\n");
	return (NULL);
}

int main(int argc, char **argv)
{
	t_philo	ph;
	int		i;

	i = 0;
	if (argc != 5 && argc != 6)
		return (wrong_arg());
	if (init_struc(&ph, argv) < 0)
		return (wrong_arg());
	if (malloc_struc(&ph) < 0)
		return (-1);
	while (i < ph.philo_nbr)
	{
		if (pthread_create(&ph.thread[i], NULL, &routine, NULL) != 0)
			return (-1);
		i++;
	}
	i = 0;
	while (i < ph.philo_nbr)
	{
		if (pthread_join(ph.thread[i], NULL) != 0)
			return (-1);
		i++;
	}
	return (0);
}