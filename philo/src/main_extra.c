/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_extra.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luguimar <luguimar@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 20:28:39 by luguimar          #+#    #+#             */
/*   Updated: 2024/04/11 07:34:13 by luguimar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	end_simulation_extra(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->nb_philo)
	{
		if (table->philos[i].last_meal + table->time_to_die < get_time())
		{
			table->simulation_end = 1;
			printf("%lld %d died\n", get_time() - table->start_time, \
				table->philos[i].id);
			pthread_mutex_unlock(&table->everything_else_mutex);
			return (1);
		}
	}
	pthread_mutex_unlock(&table->everything_else_mutex);
	return (0);
}

int	start_simulation_extra(t_table *table)
{
	int	i;

	pthread_mutex_destroy(&table->everything_else_mutex);
	i = -1;
	while (++i < table->nb_philo)
		pthread_mutex_destroy(&table->forks_mutex[i]);
	free(table->forks_mutex);
	free(table->philos);
	free(table->eat_that_meal);
	return (0);
}

void	init_philo_aux(t_table *table, int i)
{
	table->eat_that_meal[i] = 0;
	pthread_mutex_init(&table->forks_mutex[i], NULL);
	table->philos[i].id = i + 1;
	table->philos[i].last_meal = 0;
	table->philos[i].table = table;
	table->philos[i].last_meal = get_time();
}
