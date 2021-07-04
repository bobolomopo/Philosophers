/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_mem_val.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jandre <jandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/04 13:51:41 by jandre            #+#    #+#             */
/*   Updated: 2021/07/04 17:13:28 by jandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	init_values(t_philo *ph, char **argv)
{
	ph->philo_nbr = ft_atol(argv[1]);
	ph->fork_nbr = ph->philo_nbr;
	ph->time_to_die = ft_atol(argv[2]);
	ph->time_to_eat = ft_atol(argv[3]);
	ph->time_to_sleep = ft_atol(argv[4]);
	ph->is_limit = 0;
	ph->how_many_ate = malloc(sizeof(long));
	ph->is_dead = malloc(sizeof(int));
	ph->start = malloc(sizeof(int));
	ph->start_check = malloc(sizeof(int));
	ph->initial_time = malloc(sizeof(int));
	if (!ph->how_many_ate || !ph->is_dead || !ph->start
		|| !ph->initial_time || !ph->start_check)
		return (-1);
	*ph->start = 0;
	*ph->start_check = 0;
	*ph->is_dead = 0;
	*ph->how_many_ate = 0;
	return (1);
}

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
			|| ph->max_eating > INT_MAX || ph->time_to_die <= 0
			|| ph->time_to_eat <= 0 || ph->time_to_sleep <= 0
			|| ph->max_eating <= 0)
			return (-1);
	}
	return (1);
}

static int	malloc_struc(t_philo *ph)
{
	ph->last_meal_time = malloc(sizeof(int) * ph->philo_nbr);
	if (!ph->last_meal_time)
		return (-1);
	ph->thread = malloc(sizeof(pthread_t) * ph->philo_nbr);
	ph->check_die = malloc(sizeof(pthread_t) * ph->philo_nbr);
	if (!ph->thread || !ph->check_die)
		return (-1);
	return (1);
}

static int	init_struc(t_philo *ph, char **argv)
{
	if (init_struct_cond(argv, ph, 1) < 0)
		return (-1);
	if (init_values(ph, argv) < 0)
		return (-2);
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

int	init_mem_val(t_philo *ph, char **argv, int argc)
{
	int	res;

	res = 0;
	if (argc != 5 && argc != 6)
		return (-1);
	res = init_struc(ph, argv);
	if (res < 0)
		return (res);
	if (malloc_struc(ph) < 0)
		return (-3);
	return (1);
}
