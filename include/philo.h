/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jandre <jandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/19 14:56:52 by jandre            #+#    #+#             */
/*   Updated: 2021/07/10 15:39:30 by jandre           ###   ########.fr       */
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

typedef struct s_mutex {
	pthread_mutex_t	mutex;
}	t_mutex;

typedef struct s_philo {
	long			philo_nbr;
	long			fork_nbr;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			max_eating;
	long			*how_many_ate;
	int				*is_dead;
	int				*last_meal_time;
	int				*start;
	int				is_limit;
	int				*initial_time;
	t_mutex			*display_m;
	pthread_t		*thread;
	pthread_t		*check_die;
	t_mutex			*forks;
	t_mutex			*checker;
	int				index;
}	t_philo;

int		ft_atol(const char *str);
int		ft_isdigit(int c);
int		ft_isnbr(char *str);
size_t	ft_strlen(const char *str);
int		init_mem_val(t_philo *ph, char **argv, int argc);
int		init(t_philo *ph, char **argv, int argc);
int		closing(t_philo ph);
int		create_thread(t_philo ph);
int		get_time(void);
void	ft_putchar(char c);
void	ft_putnbr(int nb);
int		thinking(t_philo ph, int i, int ate);
int		eating(t_philo ph, int i, int *ate);
int		sleeping(t_philo ph, int i);
void	display_message(int status, t_philo ph, int i);
void	*routine(void *arg);
void	*check_die(void *arg);

#endif