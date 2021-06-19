/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jandre <Ajuln@hotmail.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/19 14:56:52 by jandre            #+#    #+#             */
/*   Updated: 2021/06/19 14:56:52 by jandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <unistd.h>
# include <stdlib.h>

typedef struct s_philo {
	int		philo_nbr;
	int		fork_nbr;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		max_eating;
}	t_philo;

#endif