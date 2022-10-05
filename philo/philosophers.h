/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blaurent <blaurent@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 14:51:23 by blaurent          #+#    #+#             */
/*   Updated: 2022/10/05 16:49:12 by blaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <sys/time.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <pthread.h>
# include <string.h>
#define NC	"\e[0m"
#define YELLOW	"\e[33m"
#define BYELLOW	"\e[1;33m"
#define RED	"\e[31m"
#define GREEN	"\e[32m"

typedef struct s_table
{
	int		number_of_philosopher;
	int		philo_created;
	int		to_eat;
	int		eating;
	int		end;
	int		dinner_started;
	time_t	time_to_die;
	time_t	time_to_eat;
	time_t	time_to_sleep;
	time_t	start_dinner_time;
	pthread_mutex_t	write_lock;
}	t_table;

typedef struct s_philo
{
	int				id;
	int				is_dead;
	int				is_eating;
	time_t			count_death;
	t_table			*table;
	pthread_t		thread;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
}	t_philo;

typedef struct s_dinner
{
	t_table	*table;
	t_philo	*philo;
	pthread_t	death_checker;
}	t_dinner;

void	eat(t_philo *philo);

int		init_table(t_dinner *dinner, int ac, char **av);
int		init_philo(t_dinner *dinner, int nb_philo);
void	*death_check(void *data);
void	*philosopher(void *data);

int		ft_atoi(const char *str);
void	quit(char *error, t_dinner *dinner);
time_t	get_time(void);
long int	ft_timestamp(t_philo *philo);
void	print_state(t_philo *philo, char *s);
void	ft_usleep(t_table *table, long int time_in_ms);
#endif