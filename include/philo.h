/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jandre <jandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/19 14:56:52 by jandre            #+#    #+#             */
/*   Updated: 2021/06/21 14:25:46 by jandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <limits.h>
# include <stdio.h>

typedef struct s_philo {
	long		philo_nbr;
	long		fork_nbr;
	long		time_to_die;
	long		time_to_eat;
	long		time_to_sleep;
	long		max_eating;
	pthread_t	*thread;
}	t_philo;

int		ft_atol(const char *str);
int		ft_isdigit(int c);
int		ft_isnbr(char *str);
size_t	ft_strlen(const char *str);
int		init_struc(t_philo *ph, char **argv);
int		malloc_struc(t_philo *ph);

#endif