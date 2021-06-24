#include "../include/philo.h"

int	eating(t_philo ph, int i, int last_meal)
{
	long long time;

	time = 0;
	printf("[%d] %d is eating\n", last_meal, i);
	while (time < ph.time_to_eat && get_time() - last_meal < ph.time_to_die)
	{
		usleep(10000);
		time += 10;
	}
	if (get_time() - last_meal < ph.time_to_die)
		return (1);
	else
		return (-1);
}

int	sleeping(t_philo ph, int i, int last_meal)
{
	long long time;

	time = 0;
	printf("[%d] %d is sleeping\n", last_meal, i);
	while (time < ph.time_to_sleep && get_time() - last_meal < ph.time_to_die)
	{
		usleep(10000);
		time += 10;
	}
	if (get_time() - last_meal < ph.time_to_die)
		return (1);
	else
	{
		return (-1);
	}
}

int	thinking(t_philo ph, int i, int last_meal)
{
	if (i % 2 == 0)
	{
		while (pthread_mutex_trylock(&ph.forks[i - 1].fork) != 0)
		{
			if (get_time() - last_meal > ph.time_to_die)
				return (-1);
		}
	}
	else
	{
		while (pthread_mutex_trylock(&ph.forks[i % ph.fork_nbr].fork) != 0)
		{
			if (get_time() - last_meal > ph.time_to_die)
				return (-1);
		}
	}
	printf("[%d] %d has taken a fork\n", get_time(), i);
	if (i % 2 == 0)
	{
		while (pthread_mutex_trylock(&ph.forks[i % ph.fork_nbr].fork) != 0)
		{
			if (get_time() - last_meal > ph.time_to_die)
				return (-1);
		}
	}
	else
	{
		while (pthread_mutex_trylock(&ph.forks[i - 1].fork) != 0)
		{
			if (get_time() - last_meal > ph.time_to_die)
				return (-1);
		}
	}
	printf("[%d] %d has taken a fork\n", get_time(), i);
	return (1);
}
