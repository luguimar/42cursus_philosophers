/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luguimar <luguimar@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 20:34:03 by luguimar          #+#    #+#             */
/*   Updated: 2024/06/12 23:47:17 by luguimar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	sleep_and_think(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->table->everything_else_mutex);
	if (philo->table->simulation_end)
	{
		pthread_mutex_unlock(&philo->table->everything_else_mutex);
		return (1);
	}
	printf("%lld %d is %s\n", get_time() - philo->table->start_time, \
		philo->id, str);
	pthread_mutex_unlock(&philo->table->everything_else_mutex);
	return (0);
}

int	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->everything_else_mutex);
	if (philo->table->simulation_end)
	{
		pthread_mutex_unlock(&philo->table->everything_else_mutex);
		pthread_mutex_unlock(&philo->table->forks_mutex[philo->id - 1]);
		pthread_mutex_unlock(&philo->table->forks_mutex[(philo->id) \
			% philo->table->nb_philo]);
		return (1);
	}
	printf("%lld %d is eating\n", get_time() - \
		philo->table->start_time, philo->id);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->table->everything_else_mutex);
	usleep(philo->table->time_to_eat * 1000);
	pthread_mutex_lock(&philo->table->everything_else_mutex);
	philo->table->eat_that_meal[philo->id - 1]++;
	pthread_mutex_unlock(&philo->table->everything_else_mutex);
	pthread_mutex_unlock(&philo->table->forks_mutex[philo->id - 1]);
	pthread_mutex_unlock(&philo->table->forks_mutex[(philo->id) \
		% philo->table->nb_philo]);
	return (0);
}

static int	take_forks_odd(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->forks_mutex[(philo->id) \
		% philo->table->nb_philo]);
	pthread_mutex_lock(&philo->table->everything_else_mutex);
	if (philo->table->simulation_end)
	{
		pthread_mutex_unlock(&philo->table->everything_else_mutex);
		pthread_mutex_unlock(&philo->table->forks_mutex[(philo->id) \
			% philo->table->nb_philo]);
		return (1);
	}
	printf("%lld %d has taken a fork\n", get_passed_time(philo), philo->id);
	pthread_mutex_unlock(&philo->table->everything_else_mutex);
	pthread_mutex_lock(&philo->table->forks_mutex[philo->id - 1]);
	pthread_mutex_lock(&philo->table->everything_else_mutex);
	if (philo->table->simulation_end)
	{
		pthread_mutex_unlock(&philo->table->everything_else_mutex);
		pthread_mutex_unlock(&philo->table->forks_mutex[philo->id - 1]);
		pthread_mutex_unlock(&philo->table->forks_mutex[(philo->id) \
			% philo->table->nb_philo]);
		return (1);
	}
	printf("%lld %d has taken a fork\n", get_passed_time(philo), philo->id);
	pthread_mutex_unlock(&philo->table->everything_else_mutex);
	return (0);
}

static int	take_forks_even(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->forks_mutex[philo->id - 1]);
	pthread_mutex_lock(&philo->table->everything_else_mutex);
	if (philo->table->simulation_end)
	{
		pthread_mutex_unlock(&philo->table->everything_else_mutex);
		pthread_mutex_unlock(&philo->table->forks_mutex[philo->id - 1]);
		return (1);
	}
	printf("%lld %d has taken a fork\n", get_passed_time(philo), philo->id);
	pthread_mutex_unlock(&philo->table->everything_else_mutex);
	pthread_mutex_lock(&philo->table->forks_mutex[(philo->id) \
		% philo->table->nb_philo]);
	pthread_mutex_lock(&philo->table->everything_else_mutex);
	if (philo->table->simulation_end)
	{
		pthread_mutex_unlock(&philo->table->everything_else_mutex);
		pthread_mutex_unlock(&philo->table->forks_mutex[philo->id - 1]);
		pthread_mutex_unlock(&philo->table->forks_mutex[(philo->id) \
			% philo->table->nb_philo]);
		return (1);
	}
	printf("%lld %d has taken a fork\n", get_passed_time(philo), philo->id);
	pthread_mutex_unlock(&philo->table->everything_else_mutex);
	return (0);
}

int	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		if (take_forks_even(philo))
			return (1);
	}
	else if (philo->table->nb_philo == 1)
	{
		pthread_mutex_lock(&philo->table->forks_mutex[philo->id - 1]);
		printf("%lld %d has taken a fork\n", get_passed_time(philo), philo->id);
		while (!end_simulation(philo->table, 0))
			;
		pthread_mutex_lock(&philo->table->everything_else_mutex);
		if (philo->table->simulation_end)
			return (pthread_mutex_unlock(&philo->table->everything_else_mutex), \
			pthread_mutex_unlock(&philo->table->forks_mutex[philo-> \
			id - 1]), 1);
		return (1);
	}
	else if (take_forks_odd(philo))
		return (1);
	return (0);
}
