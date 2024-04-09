/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luguimar <luguimar@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 03:24:28 by luguimar          #+#    #+#             */
/*   Updated: 2024/04/09 21:31:32 by luguimar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_philo
{
	int				id;
	int				nb_meals;
	long long int	last_meal;
	struct s_table	*table;
	pthread_t		thread;
	pthread_mutex_t	philo_mutex;
}					t_philo;

typedef struct s_table
{
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_eat;
	int				nb_meals;
	int				eat_that_meal;
	int				everyone_ate;
	int				simulation_end;
	long long int	start_time;
	pthread_mutex_t	*forks_mutex;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	nb_meals_mutex;
	pthread_mutex_t	everyone_ate_mutex;
	pthread_mutex_t	eat_that_meal_mutex;
	t_philo			*philos;
}					t_table;

long long int	get_time(void);
int				philo_atoi(const char *str);
int				end_simulation_extra(t_table *table);
int				start_simulation_extra(t_table *table);
void			init_philo_extra(t_table *table);
int				parse_args(t_table *table, int argc, char **argv);
int				sleep_philo(t_philo *philo);
int				think(t_philo *philo);
int				eat(t_philo *philo);
int				take_forks(t_philo *philo);

#endif
