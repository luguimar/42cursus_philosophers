/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luguimar <luguimar@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 20:34:03 by luguimar          #+#    #+#             */
/*   Updated: 2024/04/09 20:34:20 by luguimar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	sleep_philo(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->print_mutex);
	if (philo->table->simulation_end)
	{
		pthread_mutex_unlock(&philo->table->print_mutex);
		return (1);
	}
	printf("%lld %d is sleeping\n", get_time() - philo->table->start_time, \
		philo->id);
	pthread_mutex_unlock(&philo->table->print_mutex);
	usleep(philo->table->time_to_sleep * 1000);
	return (0);
}

int	think(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->print_mutex);
	if (philo->table->simulation_end)
	{
		pthread_mutex_unlock(&philo->table->print_mutex);
		return (1);
	}
	printf("%lld %d is thinking\n", get_time() - philo->table->start_time, \
		philo->id);
	pthread_mutex_unlock(&philo->table->print_mutex);
	usleep(philo->table->time_to_sleep * 1000);
	return (0);
}

int	eat(t_philo *philo)
{
	if (philo->table->simulation_end)
	{
		pthread_mutex_unlock(&philo->table->forks_mutex[philo->id - 1]);
		pthread_mutex_unlock(&philo->table->forks_mutex[(philo->id) \
			% philo->table->nb_philo]);
		return (1);
	}
	philo->last_meal = get_time();
	pthread_mutex_lock(&philo->table->print_mutex);
	printf("%lld %d is eating (%d time)\n", get_time() - \
		philo->table->start_time, philo->id, philo->nb_meals + 1);
	pthread_mutex_unlock(&philo->table->print_mutex);
	usleep(philo->table->time_to_eat * 1000);
	philo->nb_meals++;
	pthread_mutex_lock(&philo->table->eat_that_meal_mutex);
	philo->table->eat_that_meal++;
	pthread_mutex_lock(&philo->table->nb_meals_mutex);
	if (philo->nb_meals > philo->table->nb_meals && philo->table->eat_that_meal \
			== philo->table->nb_philo)
	{
		philo->table->nb_meals = philo->nb_meals;
		philo->table->eat_that_meal = 0;
	}
	pthread_mutex_unlock(&philo->table->nb_meals_mutex);
	pthread_mutex_unlock(&philo->table->eat_that_meal_mutex);
	pthread_mutex_unlock(&philo->table->forks_mutex[philo->id - 1]);
	pthread_mutex_unlock(&philo->table->forks_mutex[(philo->id) \
		% philo->table->nb_philo]);
	if (philo->table->simulation_end)
		return (1);
	return (0);
}

int	take_forks(t_philo *philo)
{
	if (philo->nb_meals == philo->table->nb_eat)
		return (1);
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->table->forks_mutex[philo->id - 1]);
		pthread_mutex_lock(&philo->table->print_mutex);
		if (philo->table->simulation_end)
		{
			pthread_mutex_unlock(&philo->table->print_mutex);
			pthread_mutex_unlock(&philo->table->forks_mutex[philo->id - 1]);
			return (1);
		}
		printf("%lld %d has taken a fork\n", get_time() - \
			philo->table->start_time, philo->id);
		pthread_mutex_unlock(&philo->table->print_mutex);
		if (philo->table->simulation_end)
		{
			pthread_mutex_unlock(&philo->table->forks_mutex[philo->id - 1]);
			return (1);
		}
		pthread_mutex_lock(&philo->table->forks_mutex[(philo->id) \
			% philo->table->nb_philo]);
		pthread_mutex_lock(&philo->table->print_mutex);
		if (philo->table->simulation_end)
		{
			pthread_mutex_unlock(&philo->table->print_mutex);
			pthread_mutex_unlock(&philo->table->forks_mutex[philo->id - 1]);
			pthread_mutex_unlock(&philo->table->forks_mutex[(philo->id) \
				% philo->table->nb_philo]);
			return (1);
		}
		printf("%lld %d has taken a fork\n", get_time() - \
			philo->table->start_time, philo->id);
		pthread_mutex_unlock(&philo->table->print_mutex);
		if (philo->table->simulation_end)
		{
			pthread_mutex_unlock(&philo->table->forks_mutex[philo->id - 1]);
			pthread_mutex_unlock(&philo->table->forks_mutex[(philo->id) \
				% philo->table->nb_philo]);
			return (1);
		}
	}
	else
	{
		pthread_mutex_lock(&philo->table->forks_mutex[(philo->id) \
			% philo->table->nb_philo]);
		pthread_mutex_lock(&philo->table->print_mutex);
		if (philo->table->simulation_end)
		{
			pthread_mutex_unlock(&philo->table->print_mutex);
			pthread_mutex_unlock(&philo->table->forks_mutex[(philo->id) \
				% philo->table->nb_philo]);
			return (1);
		}
		printf("%lld %d has taken a fork\n", get_time() - \
			philo->table->start_time, philo->id);
		pthread_mutex_unlock(&philo->table->print_mutex);
		pthread_mutex_lock(&philo->table->forks_mutex[philo->id - 1]);
		pthread_mutex_lock(&philo->table->print_mutex);
		if (philo->table->simulation_end)
		{
			pthread_mutex_unlock(&philo->table->print_mutex);
			pthread_mutex_unlock(&philo->table->forks_mutex[(philo->id) \
				% philo->table->nb_philo]);
			pthread_mutex_unlock(&philo->table->forks_mutex[philo->id - 1]);
			return (1);
		}
		printf("%lld %d has taken a fork\n", get_time() - \
			philo->table->start_time, philo->id);
		pthread_mutex_unlock(&philo->table->print_mutex);
		if (philo->table->simulation_end)
		{
			pthread_mutex_unlock(&philo->table->forks_mutex[(philo->id) \
				% philo->table->nb_philo]);
			pthread_mutex_unlock(&philo->table->forks_mutex[philo->id - 1]);
			return (1);
		}
	}
	return (0);
}
