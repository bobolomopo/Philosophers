/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_struc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jandre <jandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 14:14:27 by jandre            #+#    #+#             */
/*   Updated: 2021/06/25 12:45:59 by jandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	init_struct_cond(char **argv, t_philo *ph, int cond)
{
	if (cond == 1)
	{
		if (ft_isnbr(argv[1]) < 0 || ft_isnbr(argv[2]) < 0
			|| ft_isnbr(argv[3]) < 0 || ft_isnbr(argv[4]) < 0
			|| ft_strlen(argv[1]) > 10 || ft_strlen(argv[2]) > 10
			|| ft_strlen(argv[3]) > 10 || ft_strlen(argv[4]) > 10)
			return (-1);
	}
	else if (cond == 0)
	{
		if (ph->philo_nbr > INT_MAX || ph->time_to_die > INT_MAX
			|| ph->time_to_eat > INT_MAX || ph->time_to_sleep > INT_MAX
			|| ph->max_eating > INT_MAX || ph->philo_nbr < 2
			|| ph->time_to_die < 0 || ph->time_to_eat < 0
			|| ph->time_to_sleep < 0 || ph->max_eating < 0)
			return (-1);
	}
	return (1);
}

int	init_struc(t_philo *ph, char **argv)
{
	if (init_struct_cond(argv, ph, 1) < 0)
		return (-1);
	ph->philo_nbr = ft_atol(argv[1]);
	ph->fork_nbr = ph->philo_nbr;
	ph->time_to_die = ft_atol(argv[2]);
	ph->time_to_eat = ft_atol(argv[3]);
	ph->time_to_sleep = ft_atol(argv[4]);
	ph->is_limit = 0;
	ph->how_many_ate = malloc(sizeof(long));
	if (!ph->how_many_ate)
		return (-1);
	*ph->how_many_ate = 0;
	if (argv[5])
	{
		if (ft_isnbr(argv[5]) < 0 || ft_strlen(argv[5]) > 10)
			return (-1);
		ph->max_eating = ft_atol(argv[5]);
		ph->is_limit = 1;
	}
	else
		ph->max_eating = 1;
	if (init_struct_cond(argv, ph, 0) < 0)
		return (-1);
	return (1);
}

int	malloc_struc(t_philo *ph)
{
	ph->thread = malloc(sizeof(pthread_t) * ph->philo_nbr);
	if (!ph->thread)
		return (thread_error(2));
	return (1);
}

int	mutex_init(t_philo *ph)
{
	int		i;

	i = 0;
	ph->forks = malloc(sizeof(t_forks) * ph->fork_nbr);
	if (!ph->forks)
		return (thread_error(3));
	while (i < ph->fork_nbr)
	{
		pthread_mutex_init(&ph->forks[i].fork, NULL);
		i++;
	}
	return (1);
}

int	mutex_destroy(t_philo *ph)
{
	int		i;

	i = 0;
	while (i < ph->fork_nbr)
	{
		pthread_mutex_destroy(&ph->forks[i].fork);
		i++;
	}
	free(ph->forks);
	return (1);
}
