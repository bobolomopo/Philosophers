/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jandre <jandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/19 14:56:25 by jandre            #+#    #+#             */
/*   Updated: 2021/06/21 19:34:07 by jandre           ###   ########.fr       */
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

void	*routine(void *arg)
{
	int		i;
	t_philo ph;
	int				last_meal;

	ph = *(t_philo *)arg;
	i = ph.index;
	last_meal = get_time();
//	printf("[timestamp : %d]philosophers %d died\n", get_time(), i);
//	printf("[timestamp : %d]philosophers %d eating...\n", get_time(), i);
//	printf("[timestamp : %d]philosophers %d sleeping...\n", get_time(), i);
//	printf("[timestamp : %d]philosophers %d thinking...\n", get_time(), i);	
//	while (ph.max_eating >= 0)
//	{
		pthread_mutex_lock(&ph.forks[2].fork);
		usleep(500000);
		printf("[timestamp : %d] philosophers %d eating...\n", get_time(), i);
		pthread_mutex_unlock(&ph.forks[2].fork);
		if (ph.is_limit > 0)
			ph.max_eating--;
//	}
	free(arg);
	return (NULL);
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
	while (i < original.fork_nbr)
	{
		new->forks[i].fork = original.forks[i].fork;
		i++;
	}
	new->is_limit = original.is_limit;
}

int main(int argc, char **argv)
{
	t_philo	ph;
	t_philo	*each_ph;
	int		i;

	i = 0;
	if (argc != 5 && argc != 6)
		return (wrong_arg());
	if (init_struc(&ph, argv) < 0)
		return (wrong_arg());
	if (malloc_struc(&ph) < 0)
		return (-1);
	if (mutex_init(&ph) < 0)
		return (-1);
	while (i < (int)ph.philo_nbr)
	{
		each_ph = malloc(sizeof(t_philo));
		if (!each_ph)
			return (-1);
		copy_struct(ph, each_ph);
		each_ph->index = i + 1;
		if (pthread_create(&ph.thread[i], NULL, &routine, each_ph) != 0)
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
	mutex_destroy(&ph);
	return (0);
}