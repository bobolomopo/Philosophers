/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_struc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jandre <jandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 14:14:27 by jandre            #+#    #+#             */
/*   Updated: 2021/06/21 19:26:56 by jandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	init_struc(t_philo *ph, char **argv)
{
	if (ft_isnbr(argv[1]) < 0 || ft_isnbr(argv[2]) < 0 ||
		ft_isnbr(argv[3]) < 0 || ft_isnbr(argv[4]) < 0 ||
		ft_strlen(argv[1]) > 10 || ft_strlen(argv[2]) > 10 ||
		ft_strlen(argv[3]) > 10 || ft_strlen(argv[4]) > 10)
		return (-1);
	ph->philo_nbr = ft_atol(argv[1]);
	ph->fork_nbr = ph->philo_nbr;
	ph->time_to_die = ft_atol(argv[2]);
	ph->time_to_eat = ft_atol(argv[3]);
	ph->time_to_sleep = ft_atol(argv[4]);
	ph->is_limit = 0;
	if (argv[5])
	{
		if (ft_isnbr(argv[5]) < 0 || ft_strlen(argv[5]) > 10)
			return (-1);
		ph->max_eating = ft_atol(argv[5]);
		ph->is_limit = 1;
	}
	else
		ph->max_eating = 0;
	if (ph->philo_nbr > INT_MAX || ph->time_to_die > INT_MAX ||
		ph->time_to_eat > INT_MAX || ph->time_to_sleep > INT_MAX ||
		ph->max_eating > INT_MAX || ph->philo_nbr < 0 ||
		ph->time_to_die < 0 || ph->time_to_eat < 0 ||
		ph->time_to_sleep < 0 || ph->max_eating < 0)
		return (-1);
	return (1);
}

int malloc_struc(t_philo *ph)
{
	int i;

	i = 0;
	ph->thread = malloc(sizeof(pthread_t *));
	if (!ph->thread)
		return (-1);
	while (i < ph->philo_nbr)
	{
		ph->thread[i] = malloc(sizeof(pthread_t));
		if (!ph->thread[i])
			return (-1);
		i++;
	}
	return (1);
}

int mutex_init(t_philo *ph)
{
	int i;

	i = 0;
	ph->forks = malloc(sizeof(t_forks) * ph->fork_nbr);
	if (!ph->forks)
		return (-1);
	while (i < ph->fork_nbr)
	{
		pthread_mutex_init(&ph->forks[i].fork, NULL);
		i++;
	}
	return (1);
}

int	mutex_destroy(t_philo *ph)
{
	int i;

	i = 0;
	while (i < ph->fork_nbr)
	{
		pthread_mutex_destroy(&ph->forks[i].fork);
		i++;
	}
	free(ph->forks);
	return (1);
}