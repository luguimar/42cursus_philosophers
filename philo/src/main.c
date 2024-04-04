/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luguimar <luguimar@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 03:30:28 by luguimar          #+#    #+#             */
/*   Updated: 2024/04/04 04:24:43 by luguimar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	res;

	i = 0;
	res = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'
		|| str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] < '0' || str[i] > '9')
		return (-1);
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - '0');
		i++;
	}
	if (str[i] != '\0')
		return (-1);
	return (res);
}

void	sleep_philo(t_philo *philo)
{
	printf("%lld %d is sleeping\n", get_time() - philo->table->start_time, \
		philo->id);
	usleep(philo->table->time_to_sleep * 1000);
}

void	think(t_philo *philo)
{
	printf("%lld %d is thinking\n", get_time() - philo->table->start_time, \
		philo->id);
	usleep(philo->table->time_to_sleep * 1000);
}

void	eat(t_philo *philo)
{
	philo->last_meal = get_time();
	pthread_mutex_lock(&philo->table->print_mutex);
	printf("%lld %d is eating\n", get_time() - philo->table->start_time, \
		philo->id);
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
}

int	take_forks(t_philo *philo)
{
	while (philo->nb_meals > philo->table->nb_meals && philo->table-> \
		eat_that_meal != philo->table->nb_philo)
		;
	pthread_mutex_lock(&philo->table->death_mutex);
	if (philo->table->someone_dead)
	{
		pthread_mutex_unlock(&philo->table->death_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->table->death_mutex);
	pthread_mutex_lock(&philo->table->forks_mutex[philo->id - 1]);
	pthread_mutex_lock(&philo->table->print_mutex);
	printf("%lld %d has taken a fork\n", get_time() - \
		philo->table->start_time, philo->id);
	pthread_mutex_unlock(&philo->table->print_mutex);
	pthread_mutex_lock(&philo->table->forks_mutex[(philo->id) \
		% philo->table->nb_philo]);
	pthread_mutex_lock(&philo->table->print_mutex);
	printf("%lld %d has taken a fork\n", get_time() - \
		philo->table->start_time, philo->id);
	pthread_mutex_unlock(&philo->table->print_mutex);
	return (0);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (take_forks(philo))
			return (NULL);
		eat(philo);
		if (philo->table->nb_eat != -1 && philo->nb_meals \
		>= philo->table->nb_eat)
			return (NULL);
		think(philo);
		sleep_philo(philo);
	}
	return (NULL);
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
	while (i < table->nb_philo)
	{
		if (pthread_join(table->philos[i].thread, NULL))
			return (1);
		i++;
	}
	return (0);
}

void	init_philo_extra1(t_table *table)
{
	table->everyone_ate = 0;
	table->eat_that_meal = 0;
	pthread_mutex_init(&table->print_mutex, NULL);
	pthread_mutex_init(&table->death_mutex, NULL);
	pthread_mutex_init(&table->nb_meals_mutex, NULL);
	pthread_mutex_init(&table->everyone_ate_mutex, NULL);
	pthread_mutex_init(&table->eat_that_meal_mutex, NULL);
}

void	init_philo_extra(int i, t_table *table)
{
	table->philos[i].id = i + 1;
	table->philos[i].nb_meals = 0;
	table->philos[i].last_meal = 0;
	table->philos[i].table = table;
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
		init_philo_extra(i, table);
	}
	table->nb_meals = 0;
	table->someone_dead = 0;
	init_philo_extra1(table);
	return (0);
}

int	parse_args(t_table *table, int argc, char **argv)
{
	table->nb_philo = ft_atoi(argv[1]);
	table->time_to_die = ft_atoi(argv[2]);
	table->time_to_eat = ft_atoi(argv[3]);
	table->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		table->nb_eat = ft_atoi(argv[5]);
	else
		table->nb_eat = -1;
	if (table->nb_philo < 1 || table->time_to_die < 1 || table->time_to_eat < 1
		|| table->time_to_sleep < 1 || (argc == 6 && table->nb_eat < 0))
		return (1);
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
