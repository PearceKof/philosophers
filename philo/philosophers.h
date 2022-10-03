/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blaurent <blaurent@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 14:51:23 by blaurent          #+#    #+#             */
/*   Updated: 2022/10/03 16:10:55 by blaurent         ###   ########.fr       */
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
	int		nb_of_philo;
	int		to_eat;
	int		eating;
	int		finished;
	int		waiting;
	time_t	time_die;
	time_t	time_eat;
	time_t	time_sleep;
	time_t	start_dinner_time;
	pthread_mutex_t	mut;
}	t_table;

typedef struct s_philo
{
	int				id;
	int				is_dead;
	int				eating;
	time_t			count_death;
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

int	init_table(t_dinner *dinner, int ac, char **av);
int	init_philo(t_dinner *dinner, int nb_philo);
int	ft_atoi(const char *str);

#endif