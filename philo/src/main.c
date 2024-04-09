/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luguimar <luguimar@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 03:30:28 by luguimar          #+#    #+#             */
/*   Updated: 2024/04/09 20:36:24 by luguimar         ###   ########.fr       */
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
		if (think(philo))
			return (NULL);
		if (sleep_philo(philo))
			return (NULL);
	}
	return (NULL);
}

int	end_simulation(t_table *table)
{
	pthread_mutex_lock(&table->nb_meals_mutex);
	if (table->nb_eat != -1 && table->nb_meals >= table->nb_eat)
	{
		pthread_mutex_lock(&table->print_mutex);
		printf("Everyone ate %d meals\n", table->nb_meals);
		pthread_mutex_unlock(&table->print_mutex);
		pthread_mutex_unlock(&table->nb_meals_mutex);
		return (1);
	}
	pthread_mutex_unlock(&table->nb_meals_mutex);
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
	while (++i < table->nb_philo)
	{
		pthread_mutex_init(&table->forks_mutex[i], NULL);
		table->philos[i].id = i + 1;
		table->philos[i].nb_meals = 0;
		table->philos[i].last_meal = 0;
		table->philos[i].table = table;
		table->philos[i].last_meal = get_time();
		pthread_mutex_init(&table->philos[i].philo_mutex, NULL);
	}
	table->nb_meals = 0;
	init_philo_extra(table);
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
