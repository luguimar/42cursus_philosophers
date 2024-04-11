/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luguimar <luguimar@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 03:30:28 by luguimar          #+#    #+#             */
/*   Updated: 2024/04/11 07:33:33 by luguimar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (take_forks(philo))
			return (NULL);
		if (eat(philo))
			return (NULL);
		if (sleep_and_think(philo, "sleeping"))
			return (NULL);
		usleep(philo->table->time_to_sleep * 1000);
		if (sleep_and_think(philo, "thinking"))
			return (NULL);
	}
	return (NULL);
}

int	end_simulation(t_table *table)
{
	int	i;
	int	ate_all;

	i = -1;
	ate_all = 0;
	//pthread_mutex_lock(&table->everything_else_mutex);
	while (++i < table->nb_philo)
	{
		if (table->nb_eat != -1 && table->eat_that_meal[i] >= table->nb_eat)
			ate_all++;
		if (ate_all == table->nb_philo)
		{
			table->simulation_end = 1;
		//	pthread_mutex_unlock(&table->everything_else_mutex);
			return (1);
		}
	}
	return (end_simulation_extra(table));
}

int	start_simulation(t_table *table)
{
	int	i;

	table->start_time = get_time();
	i = 0;
	while (i < table->nb_philo)
	{
		if (pthread_create(&table->philos[i].thread, NULL, &routine,
				&table->philos[i]))
			return (1);
		i++;
	}
	i = 0;
	while (!end_simulation(table))
		;
	while (i < table->nb_philo)
	{
		if (pthread_join(table->philos[i].thread, NULL))
			return (1);
		i++;
	}
	return (start_simulation_extra(table));
}

int	init_philo(t_table *table, int i)
{
	table->forks_mutex = malloc(sizeof(pthread_mutex_t) * table->nb_philo);
	if (!table->forks_mutex)
		return (1);
	table->philos = malloc(sizeof(t_philo) * table->nb_philo);
	if (!table->philos)
	{
		free(table->forks_mutex);
		return (1);
	}
	table->eat_that_meal = malloc(sizeof(int) * table->nb_philo);
	if (!table->eat_that_meal)
	{
		free(table->forks_mutex);
		free(table->philos);
		return (1);
	}
	while (++i < table->nb_philo)
		init_philo_aux(table, i);
	table->simulation_end = 0;
	pthread_mutex_init(&table->everything_else_mutex, NULL);
	return (0);
}

int	main(int argc, char **argv)
{
	t_table	table;

	if (argc < 5 || argc > 6)
	{
		printf("Error: Wrong number of arguments\n");
		return (1);
	}
	if (parse_args(&table, argc, argv))
	{
		printf("Error: Invalid arguments\n");
		return (1);
	}
	if (init_philo(&table, -1))
	{
		printf("Error: Failed to initialize philosophers\n");
		return (1);
	}
	if (start_simulation(&table))
	{
		printf("Error: Failed to start simulation\n");
		return (1);
	}
	return (0);
}
