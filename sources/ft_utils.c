/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jandre <jandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 16:36:23 by jandre            #+#    #+#             */
/*   Updated: 2021/06/23 16:59:23 by jandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	thread_error(int status)
{
	if (status == 0)
		printf("ERROR : could not create thread\n");
	if (status == 1)
		printf("ERROR : could not join thread\n");
	if (status == 2)
		printf("ERROR : could not malloc structures\n");
	if (status == 3)
		printf("ERROR : could not malloc mutexes\n");
	return (-1);
}