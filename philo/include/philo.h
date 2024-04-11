/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luguimar <luguimar@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 03:24:28 by luguimar          #+#    #+#             */
/*   Updated: 2024/04/11 10:54:05 by luguimar         ###   ########.fr       */
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
	long long int	last_meal;
	struct s_table	*table;
	pthread_t		thread;
}					t_philo;

typedef struct s_table
{
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_eat;
	int				*eat_that_meal;
	int				simulation_end;
	long long int	start_time;
	pthread_mutex_t	*forks_mutex;
	pthread_mutex_t	everything_else_mutex;
	t_philo			*philos;
}					t_table;

long long int	get_time(void);
int				philo_atoi(const char *str);
int				end_simulation_extra(t_table *table, int print);
int				start_simulation_extra(t_table *table);
int				parse_args(t_table *table, int argc, char **argv);
int				sleep_and_think(t_philo *philo, char *str);
int				eat(t_philo *philo);
int				take_forks(t_philo *philo);
void			init_philo_aux(t_table *table, int i);
long long int	get_passed_time(t_philo *philo);
long long int	get_time_to_think(t_philo *philo);
int				end_simulation(t_table *table, int print);

#endif
