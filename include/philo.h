/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jandre <jandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/19 14:56:52 by jandre            #+#    #+#             */
/*   Updated: 2021/06/23 16:48:59 by jandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <limits.h>
# include <stdio.h>
# include <sys/time.h>

typedef struct s_forks {
	pthread_mutex_t	fork;
}	t_forks;

typedef struct s_philo {
	long			philo_nbr;
	long			fork_nbr;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			max_eating;
	int				is_limit;
	pthread_t		*thread;
	t_forks			*forks;
	int				index;
}	t_philo;

int		ft_atol(const char *str);
int		ft_isdigit(int c);
int		ft_isnbr(char *str);
size_t	ft_strlen(const char *str);
int		init_struc(t_philo *ph, char **argv);
int		malloc_struc(t_philo *ph);
int		mutex_init(t_philo *ph);
int		get_time(void);
void	*routine(void *arg);
int		mutex_destroy(t_philo *ph);
int		thread_error(int status);

#endif