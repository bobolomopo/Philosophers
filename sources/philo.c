/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jandre <Ajuln@hotmail.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/19 14:56:25 by jandre            #+#    #+#             */
/*   Updated: 2021/06/19 14:56:25 by jandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	wrong_arg(void)
{
	write(1, "Error : use the program like :\n./philo \"number of philosopher\"
 \"time to die\" \"time to eat\" \"time to sleep\" \"optionnal : max number of\
  eating");
	return (1);
}

int main(int argc, char **argv)
{
	char *str;

	if (argc != 5 && argc != 6)
		return (wrong_arg());
	write(1, argv[2], 1);
	return (0);
}