/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_extra.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luguimar <luguimar@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 20:28:39 by luguimar          #+#    #+#             */
/*   Updated: 2024/04/09 22:32:36 by luguimar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	end_simulation_extra(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->nb_philo)
	{
		pthread_mutex_lock(&table->philos[i].philo_mutex);
		if (table->philos[i].last_meal + table->time_to_die < get_time())
		{
			table->simulation_end = 1;
			pthread_mutex_lock(&table->print_mutex);
			printf("%lld %d died\n", get_time() - table->start_time, \
				table->philos[i].id);
			pthread_mutex_unlock(&table->print_mutex);
			pthread_mutex_unlock(&table->philos[i].philo_mutex);
			pthread_mutex_unlock(&table->simulation_end_mutex);
			return (1);
		}
		pthread_mutex_unlock(&table->philos[i].philo_mutex);
		pthread_mutex_unlock(&table->simulation_end_mutex);
	}
	return (0);
}

int	start_simulation_extra(t_table *table)
{
	int	i;

	pthread_mutex_destroy(&table->print_mutex);
	pthread_mutex_destroy(&table->nb_meals_mutex);
	pthread_mutex_destroy(&table->everyone_ate_mutex);
	pthread_mutex_destroy(&table->eat_that_meal_mutex);
	i = -1;
	while (++i < table->nb_philo)
	{
		pthread_mutex_destroy(&table->forks_mutex[i]);
		pthread_mutex_destroy(&table->philos[i].philo_mutex);
	}
	free(table->forks_mutex);
	free(table->philos);
	return (0);
}

void	init_philo_extra(t_table *table)
{
	table->everyone_ate = 0;
	table->eat_that_meal = 0;
	table->simulation_end = 0;
	pthread_mutex_init(&table->print_mutex, NULL);
	pthread_mutex_init(&table->nb_meals_mutex, NULL);
	pthread_mutex_init(&table->everyone_ate_mutex, NULL);
	pthread_mutex_init(&table->eat_that_meal_mutex, NULL);
	pthread_mutex_init(&table->simulation_end_mutex, NULL);
}
