/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luguimar <luguimar@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 20:00:10 by luguimar          #+#    #+#             */
/*   Updated: 2024/04/09 22:04:49 by luguimar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

long long int	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	philo_atoi(const char *str)
{
	int				i;
	long long int	nb;

	i = 0;
	nb = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'
		|| str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb = nb * 10 + (str[i] - '0');
		i++;
	}
	if (str[i] != '\0' || nb > 2147483647)
		return (-1);
	return ((int)nb);
}

int	parse_args(t_table *table, int argc, char **argv)
{
	table->nb_philo = philo_atoi(argv[1]);
	table->time_to_die = philo_atoi(argv[2]);
	table->time_to_eat = philo_atoi(argv[3]);
	table->time_to_sleep = philo_atoi(argv[4]);
	if (argc == 6)
		table->nb_eat = philo_atoi(argv[5]);
	else
		table->nb_eat = -1;
	if (table->nb_philo < 1 || table->time_to_die < 1 || table->time_to_eat < 1
		|| table->time_to_sleep < 1 || (argc == 6 && table->nb_eat < 0))
		return (1);
	return (0);
}
